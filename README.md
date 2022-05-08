# Golf Ace

![](https://raw.githubusercontent.com/nickbild/golf_ace/main/media/putting_logo_sm.jpg)

<p align="center">
<img src="https://raw.githubusercontent.com/nickbild/golf_ace/main/media/teaser.gif">
</p>

## How It Works

When you are ready to putt, press the button on the handle of the putter.  An accelerometer onboard the Arduino Nano 33 IoT will begin recording measurements as you putt.  After the putt, an RGB LED on the head of the putter will give feedback -- a green light indicates that your form closely resembled that of the pro golfer that the putter was trained to recognize; red means that your technique was off.

In order for the putter to recognize proper putting technique, a K-means clustering algorithm (for anomaly detection) was trained on a set of accelerometer data collected from an instrumented putter.  Ideally, this data would be collected from professional golfers, which would allow golfers to buy a putter that teaches them to putt like their favorrite pro golfer.  But, since there are no pro golfers that owe me a favor, for this prototype, I stood in as the "pro".  I am, after all, a winner of the GrandMaster Tournament of Champions Invitational minigolf tournament (which may or may not have been invented by myself and a few friends), so that should suffice for the occasion.  To simplify building/training/deploying this model, I used Edge Impulse.

The Arduino sketch can be [found here](https://github.com/nickbild/golf_ace/tree/main/arduino).

One limitation of this device is that it is only capable of telling you if you have your technique right or not.  It cannot tell you *what* you need to do differently.  I envision a putter like this coming packaged with a video and/or written instructions from the golfer it was trained on explaining their technique.  Then one could use that as the target they are working towards, with the putter offering feedback as to whether or not the target is being met.

## Media

YouTube: https://www.youtube.com/watch?v=0Lobf9xCVeI

![](https://raw.githubusercontent.com/nickbild/golf_ace/main/media/putting_sm.jpg)

![](https://raw.githubusercontent.com/nickbild/golf_ace/main/media/hardware_zoom_sm.jpg)

![](https://raw.githubusercontent.com/nickbild/golf_ace/main/media/club_head_top_sm.jpg)

![](https://raw.githubusercontent.com/nickbild/golf_ace/main/media/club_head_side_sm.jpg)

![](https://raw.githubusercontent.com/nickbild/golf_ace/main/media/full_club_sm.jpg)

![](https://raw.githubusercontent.com/nickbild/golf_ace/main/media/club_handle_sm.jpg)

## Bill of Materials

- 1 x Arduino Nano 33 IoT
- 1 x 4-pin 5050 RGB LED
- 1 x 3.7V to 5.0V power boost converter
- 1 x 400 mAh LiPo battery
- 1 x Micro USB breakout board
- 1 x Pushbutton
- 1 x Golf putter
- Miscellaneous wire

## About the Author

[Nick A. Bild, MS](https://nickbild79.firebaseapp.com/#!/)
