#!/usr/bin/env python3
import urllib, json, sys
from random import randint
from threading import Thread
from time import sleep
from sense_hat import SenseHat
from urllib.error import URLError
from urllib.request import urlopen

STATE_OK = 'SUCCESS'
STATE_WARN = 'UNSTABLE'
STATE_ERR = 'FAILURE'

boot_up = True
building = False
state = 'SUCCESS'
sense = SenseHat()

class Display(Thread):
    def __init__(self):
      self._blink = False
      self.b = (0, 0, 255) # Blue
      self.w = (255, 255, 255) # White
      self.x = (0, 0, 0) # Black

    @property
    def blink(self):
      return self._blink

    @property
    def r(self):
      return (255, 50, 50) if self._blink else (255, 0, 0)

    @property
    def g(self):
      return (50, 255, 50) if self._blink else (0, 255, 0)

    @property
    def y(self):
      return (255, 255, 50) if self._blink else (255, 255, 0)

    def __success_pixels(self):
        x = self.x
        g = self.g
        return [
            x, x, x, x, x, x, x, x,
            x, g, g, x, x, g, g, x,
            x, g, g, x, x, g, g, x,
            x, x, x, x, x, x, x, x,
            g, x, x, x, x, x, x, g,
            g, g, g, g, g, g, g, g,
            x, g, x, x, x, x, g, x,
            x, x, g, g, g, g, x, x
        ]

    def __warning_pixels(self):
        x = self.x
        y = self.y
        return [
            y, y, y, x, x, y, y, y,
            y, y, y, x, x, y, y, y,
            y, y, y, x, x, y, y, y,
            x, x, x, x, x, x, x, x,
            x, x, x, x, x, x, x, x,
            x, y, y, y, y, y, y, x,
            x, y, y, y, y, y, y, x,
            x, x, x, x, x, x, x, x
        ]

    def __error_pixels(self):
        x = self.x
        r = self.r
        b = self.b
        return [
            x, x, x, x, x, x, x, x,
            r, r, r, x, x, r, r, r,
            r, r, r, x, x, r, r, r,
            r, r, r, x, x, r, r, b,
            x, x, x, x, x, x, x, b,
            x, x, r, r, r, r, x, x,
            x, r, r, x, x, r, r, x,
            x, r, x, x, x, x, r, x
        ]

    def __blink_generator(self):
        while True:
            if building:
                yield True
                yield False
            else:
                yield False

    def run(self):
        blinker = self.__blink_generator()
        while True:
            if boot_up:
                sense.set_pixel(randint(0, 7), randint(0, 7), randint(0, 255), randint(0, 255), randint(0,255))
                sleep(0.2)
                sense.set_pixel(randint(0, 7), randint(0, 7), 0, 0, 0)
                sleep(0.2)
            else:
                self._blink = next(blinker)
                pixels = self.__success_pixels()
                if state == STATE_WARN:
                    pixels = self.__warning_pixels()
                elif state == STATE_ERR:
                    pixels = self.__error_pixels()
                sense.set_pixels(pixels)
                sleep(0.75)

def update():
    global boot_up
    global building
    global state
    try:
        contents = urlopen("http://192.168.43.159:8887/server.json").read().decode("utf-8")
        json_object = json.loads(contents)
        boot_up = False

        temp_state = STATE_OK
        temp_building = False
        for job in json_object['jobs']:
            temp_building = temp_building or (job['lastBuild']['building'])
            if job['lastBuild']['result'] == STATE_ERR:
                temp_state = STATE_ERR
            if job['lastBuild']['result'] == STATE_WARN and temp_state == STATE_OK:
                temp_state = STATE_WARN
        state = temp_state
        building = temp_building
    except URLError:
        boot_up = True

def main():
    update()
    Display().start()
    while True:
        update()
        sleep(2)

main()
