# What is this?
- A TUI pomodoro timer with added functionality to locally store the given time
# Features
- See remaining time and how many cycles have been completed out of the total -> Work 1/3, time remaining: 20:30
- Be able to quit at any time with a short summary (start time, end time, time spent working and breaks) being either written to a file
- Be able to pause the timer
# Installation
- at this time the only officially supported way to install is building it on pretty much any linux distribution
- if you're using windows I sadly can't help you, since I don't use it
## Build
- make sure you have both ``gcc`` and ``make`` - you most likely won't have to install these on any linux distribution
- then you can:
1. clone the repository
2. navigate into the cloned directory
3. ``make``
4. your executable will be in the build directory named pomodoro
- After that you can add it to your path in order to make it launchable or whatever your heart desires :D   
# Switches
- All of these are optional
**-w** 
- how many minutes should each work cycle have. **Default: 25 min.**   

**-b**  
- how many minutes should each break have. **Default: 5 min**  

**-l**  
- how many minutes should each long break have. **Default: 15 min**
  
**-n**  
- what is the name activity you're doing. **Default: no name-> ""**

## Sample use  
- Sets a pomodoro timer with 2 work cycles each 20 minutes  
```
pomodoro -w20 -l15 -b3
```
## Todo
- tag and search/filter based on them
- online sync
# Why?
Even though the app that I use for time tracking has a pomodoro mode, the mode is fairly lack luster, mainly what I miss is a notification for end and start of breaks.
So I thought I would make a simple one as a exercise. There are a decent amount of alternatives that are most likely going to be more feature rich than this. The main goal is for this to be pretty much as simple as it can possibly be and refresh myself on C
