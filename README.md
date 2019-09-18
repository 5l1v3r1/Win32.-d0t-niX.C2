# N0T-iLLerka.X

A C/C++ recreation off the original Win32.VB.Illerka.C Virus by [Michael [APFX]](https://www.youtube.com/channel/UCDo-73OtSjnMKVIEidGu2Xw) (AppleFanXXX)

Demonstration-Video of the Original:\
<a href="https://www.youtube.com/watch?v=HnRm9DBWzY8"><img align="" height="180" src="https://img.youtube.com/vi/HnRm9DBWzY8/maxresdefault.jpg" alt="Destroying a Windows 7 PC with Trojan.Win32.Illerka.C"></a>

## About this Project
I want to recreate the Illerka.C Virus but using more efficent C/C++ instead of Visual-Basic\
(in which the original was coded)

I don't know why Im doing this (don't ask why)\
(Hint: I still don't know why, but it should give newcommers some insights into malware development)

## This Project is under Development
- MessageBox Fuctions are for Debuging purposes and will be removed later on\
(~~Update: might be excluded with a #ifdef flag, but im not sure~~)\
(they're now excluded by undefining DEBUG in der Headerfile, so they wont need to be removed)

- ~~Im now utilizing the goto function (which I wanted to avoid (why should be clear) but it was the most efficient way to do the CleanUp (better for readability and easier for me to code) but it shouldn't effect the Process itself (atleast i hope so))~~\
Yeahh... turns out this wasn't such a great Idea...\
It actualy caused the exeact opposite effect of what I wanted and that even though it was only one goto address\
Atleast I now know that I should avoid this fuction under any circumstances :D

- I have decided to remove the Bomb-Omb Icon in favor of smaller filesize and well... working with .ico Files is absolut garbage, trust me.

- Also fixed a bug that prevented the malware to even run\
(I forgot that the `CopyFile` function is unable to create a Directory in the first place so the function would always fail, NICE.\
Even better was that I hadn't implemented proper Error Handling then, which made it even harder to even find what was causing the Issue. (spend 2 hours basically doing nothing, a moment I always **ALWAYS** hate, and so does everybody else do.))

Further Information will allways be posted/updated accordingly...

## Next Update:
This is a list of stuff that will/might be implemented in the next Update:

- [x] The Directory Iterator / Directory Infector (the main Payload that is responsible to spread the Malware across the System and corrupt Files)
- [x] Host Persistency (set the HostProcess to a System critical state incase of unwanted termination to "shutdown" (BSoD))
- [ ] The Filecorruptor (a part of the Malware that will be responsible to corrupt files by overwritting them with random data)
- [ ] The WatchDog (an alternative to the previous Point to still protect the host incase that fuction fails)
- [ ] RegProtections (disabling Windows utilities that could be used by the user to regain power over the System)
