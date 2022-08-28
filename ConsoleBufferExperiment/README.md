# Console Buffer Experiment

During the previous Bitmap_to_ASCII Experiment it had came to my attention that the frames could not be printed fast enough to the windows console. I wanted to find a way to solve this problem. I found out about Console Buffers from the windows.h library, which to a degree solved my problems.

At first I had to understand how it all worked since the resources on this topic were a lot more scarce than I was used to. I worked with what I had and experimented with what I could find. 

## Results
  
Buffers allow frames to be prepared while still in the background calling ```WriteConsoleOutputCharacter(...)``` and ```FillConsoleOutputAttribute(...)```  to be revealed when ```SetConsoleActiveScreenBuffer(...)``` gets called. With this method the flickering frames problem was resolved, which was due to chars not being output fast enough to form the frame, resulting in sort of a horizontal scanning effect. 

Since it was now possible to incorperate colors into my buffers. I started by giving writing ```' '``` throughout the buffer and changing the color of another section using a nested for loop scanning the coordinates. The resulting screen made me realize although the frame rate was higher than reguler cout, they were not instantenous and I could once again see the background flickering! With every frame the background got painted and then the inner section got horizontally scanned and got painted. As the inner section could not get painted fast enough, it was possible to see the inner sections colours geting changed in a horizontal scan motion, once again causing "flickering". I got through this problem by having two buffers and toggling between them. The Buffer to be the next frame gets prepared and activated once it is ready instead of getting activated and prepared while visible. That ceased the flickering. (See ```strobe_(epilepsy-warning).gif```)

Now that the flickering was gone I decided I wanted to try making something colourful with all I have learned. So I wrote the rainbow function that output a diagonal rainbow pattern that moved on char left on each frame. Since every block was of another colour, each block had to be changed for each frame which meant it would take plenty of time for the next frame buffer to be ready which dropped the frame rate significantly. (See ```rainbow.gif```)

<p align="center" >
<img src="https://github.com/MisterNimbus/Experiments/blob/master/ConsoleBufferExperiment/rainbow.gif" width="65%" />
<div align="center">
  rainbow.gif
  </div>
</p>  

To solve this problem I thought of preparing all frames(Buffers) first and just cycling through them, which worked nicely allowing higher frame rates. (See ```rainbow_premade_frames.gif```) However this method can only be resorted when the frames are known beforehand. It would not be possible to use this method for a game or a live webcam. It would however be possible to use screen buffers just to output strings fast, since it is the number of times console buffer manipulation functions get called that takes time and not the length of the string or area to be manipulated. The rainbow case is the worst example for this instance since the color manipulation function gets called the maximum amount of times(for every char).

<p align="center" >
<img src="https://github.com/MisterNimbus/Experiments/blob/master/ConsoleBufferExperiment/rainbow_premade_frames.gif" width="65%" />
<div align="center">
  rainbow_premade_frames.gif
  </div>
</p>  

As next, I am planning to write a program to turn images or even gifs into ASCII Art with color.

Cheers!
