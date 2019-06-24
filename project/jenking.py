#!/usr/bin/env python3
import urllib, json, sys
from threading import Thread
from time import sleep
# from sense_hat import SenseHat
from urllib.error import URLError
from urllib.request import urlopen

boot_up = True
building = False
state = 'SUCCESS'
# sense = SenseHat()

class Display(Thread):
    g = '#'#(0, 255, 0) # Green
    r = '#'#(255, 0, 0) # Red
    y = '#'#(255, 255, 0) # Yellow
    b = 'O'#(0, 0, 255) # Blue
    w = '!'#(255, 255, 255) # White
    x = ' '#(0, 0, 0) # Black

    def success_pixels(self):
        x = Display.x
        g = Display.g
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

    def warning_pixels(self):
        x = Display.x
        y = Display.y
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

    def error_pixels(self):
        x = Display.x
        r = Display.r
        b = Display.b
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

    def blink_generator(self):
        while True:
            if building:
                yield True
                yield False
            else:
                yield False

    def blink(self, value):
        if value:
            Display.g = '*'#(50, 255, 50) # Green
            Display.r = '*'#(255, 50, 50) # Red
            Display.y = '*'#(255, 255, 50) # Yellow
        else:
            Display.g = '#'#(0, 255, 0) # Green
            Display.r = '#'#(255, 0, 0) # Red
            Display.y = '#'#(255, 255, 0) # Yellow

    def run(self):
        blinker = self.blink_generator()
        while boot_up:
            # TESTING
            sys.stdout.write('\033[2J\033[H') # clear screen
            sys.stdout.write('booting')
            sys.stdout.flush()

            # PRODUCTION
            # sense.set_pixel(randint(0, 7), randint(0, 7), randint(0, 255), randint(0, 255), randint(0, 255))
            sleep(0.02)

        while True:
            self.blink(next(blinker))
            pixels = self.success_pixels()
            if state == 'UNSTABLE':
                pixels = self.warning_pixels()
            elif state == 'FAILURE':
                pixels = self.error_pixels()
            
            # TESTING
            sys.stdout.write('\033[2J\033[H') # clear screen
            pixels = list(''.join(l + '\n' * (n % 8 == 7) for n, l in enumerate(pixels)))
            sys.stdout.write(''.join(pixels))
            sys.stdout.flush()

            # PRODUCTION
            # sense.set_pixels(pixels)

            sleep(0.75)

def update():
    global boot_up
    global building
    global state
    try:
        contents = urlopen("http://localhost:8887/server.json").read()
        json_object = json.loads(contents)
        boot_up = False

        temp_state = 'SUCCESS'
        temp_building = False
        for job in json_object['jobs']:
            temp_building = temp_building or (job['lastBuild']['building'])
            if job['lastBuild']['result'] == 'FAILURE':
                temp_state = 'FAILURE'
            if job['lastBuild']['result'] == 'UNSTABLE' and temp_state == 'SUCCESS':
                temp_state = 'UNSTABLE'
        state = temp_state
        building = temp_building
    except URLError:
        pass

def main():
    update()
    Display().start()
    while True:
        update()
        sleep(2)

main()