# N0T-iLLerka.X [.niX]

A C/C++ (MSVC) recreation off the original Win32.VB.Illerka.C Virus by [Michael [APFX]](https://www.youtube.com/channel/UCDo-73OtSjnMKVIEidGu2Xw) (AppleFanXXX)

Demonstration-Video of the Original:\
<a href="https://www.youtube.com/watch?v=HnRm9DBWzY8"><img height="180" src="https://img.youtube.com/vi/HnRm9DBWzY8/maxresdefault.jpg" alt="Destroying a Windows 7 PC with Trojan.Win32.Illerka.C"></a>

## About this Project
I wanted to recreate the Illerka.C Virus but using more efficent C/C++ instead of Visual-Basic (in which the original was coded)\
Aswell as that I want to add more functionality to it.
 
I don't know why Im doing this (don't ask why)\
(Hint: I still don't know why, but it should give newcommers some insights into malware development)

I should also note that this project is a just-for-fun project, it's basically a playground for me to test new stuff I've learned.\
This project is also very similar to two older projects of mine:
- hDir 5: a Malware installer (this never got published on my Github but you can find the source on YouTube though)\
  compared to this project hDir 5 was a piece of garbage (well I've written it about 2 years ago which was when I started learing C/C++)
- COBRA-6: basically Illerka.C's main Payload, but poorly done (this never got published at all and probably for good,
  I don't even know if I still have the original source but Im not even sure if I want to take a second look at it.)

Also this is my first own "big" project. (atleast to me)

## This Project is under Development
- MessageBox Fuctions are for Debuging purposes and will be removed later on\
  (~~Update: might be excluded with a #ifdef flag, but im not sure~~)\
  (they're now excluded by undefining DEBUG in der Headerfile, so they wont need to be removed)

- ~~Im now utilizing the goto function
  (which I wanted to avoid (why should be clear) but it was the most efficient way to do the CleanUp
  (better for readability and easier for me to code) but it shouldn't effect the Process itself (atleast i hope so))~~\
  Yeahh... turns out this wasn't such a great Idea...\
  It actualy caused the exeact opposite effect of what I wanted and that even though it was only one goto address\
  Atleast I now know that I should avoid this fuction under any circumstances :D

- I have decided to remove the Bomb-Omb Icon in favor of smaller filesize and well...
  working with .ico Files is absolut garbage, trust me.

- Also fixed a bug that prevented the malware to even run\
  (I forgot that the `CopyFile` function is unable to create a Directory in the first place so the function would always fail, NICE.\
  Even better was that I hadn't implemented proper Error Handling then, which made it even harder to even find what was causing the Issue.
  (spend 2 hours basically doing nothing, a moment I always **ALWAYS** hate, and so does everybody else do.))

- I've now implemented a precompiled header file wanting to find out how much and if it even would improve compile time
  (which was about 10 - 12 sec before) and holyshit it does.\
  This precompiled header shortens the compiletime down to about 2 sec which is extremly nice for a project like this that needs to be debugged alot.\
  (Though working with a PCH in VS with multiple directories is horrible sadly, but atleast you can get used to it.)

- I've implemented a better usage of VS's Build Configuration.\
  Release will be the same as before, Debug however can be used now.\
  This will compile the Malware as a Debug build (obviously), still making use of the precompiled headers.\
  It will also automatically define the DEBUG flag.\
  I've also removed the x64 Configuration from the Project.

Further Information will allways be posted/updated accordingly...

## Screenshots:
First successfull launch of the Malware:\
<a><img align="center" src="GitRes/MSEdge-Win10-VMWare-2019-09-18-21-44-00.png" alt="Windows 10 VM Screenshot"></a>

## Next Update:
This is a list of stuff that will/might be implemented in the next Update:

- [x] The Filecorruptor (a part of the Malware that will be responsible to corrupt files by overwritting them with random data)
- [x] RegProtections (disabling Windows utilities that could be used by the user to regain power over the System)
- [x] Semaphore (limit the amout of /exec processes executing their payload)\
  This might actually be cut, because the original intention of utilization is prettymuch dead.\
  If I don't utilize it for something else in the 1.0 Release this will be left behind and reserved for the future

Im getting really close to being done with this, (Im not anymore as I've discovered) 
so Version ~~0.4.9~~ 0.5.1 might be the last dev-Version (cause it will include everything that I had planed for this Malware 
(If i can even trust myself)) and Version 0.5.x might be already the 1.0 Release.\
Obviously it will still take "some time" (are you sure about that ?) until Im able to publish the 1.0 Release.

I've planned to completely go over my Code, from the start to the end, after the last dev-Version release.
I want to find every little mistake I did (if even possible) and look for anything in my code that I could improve.\
(update: Im actually in the process of that right now, but it's a lot and it will take time, a lot of time)

~~(The Version 1.0 Release will probably be in 1 to 2 weeks depending on how much time I have on my hand)~~\
(update: sadly this won't be possible, the release probably won't happen next week)

## ToDo list:
- Improve `fnErrorHandlerW`
- Improve FileCorrupt0r
- Improve Protections (- add threads that activly monitor programms like `taskmgr.exe`)
- If UAC is required launch with CMD (Stealth)
- Cut Semaphore utilization
- start to implement dropper functionality\
  (I've started to play around with DLL's and well it seems like that I'll have to explicitly link them,
  if I want to do it like I've planned/intended it to do it (if I even do it))
