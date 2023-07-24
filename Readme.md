# Features
- See remaining time and how many cycles have been completed out of the total -> Work 1/3, time remaining: 20:30
- Be able to quit at any time with a short summary (start time, end time, time spent working and breaks) being either written to a file or to stdout.
# Switches
**-w**, **--work**  
- how many minutes should each work cycle have. **Default: 25 min.**   

**-b**, **--break**  
- how many minutes should each break have. **Default: 5 min**  

**-l**, **--long**  
- how many minutes should each long break have. **Default: 15 min**  

## Sample use  
- Sets a pomodoro timer with 2 work cycles each 20 minutes  
```
pomodoro -w20 -l15 -b3
```
# Why?
Even though the app that I use for time tracking has a pomodoro mode, the mode is fairly lack luster, mainly what I miss is a notification for end and start of breaks.
So I thought I would make a simple one as a exercise. There are a decent amount of alternatives that are most likely going to be more feature rich than this. The main goal is for this to be pretty much as simple as it can possibly be and refresh myself on C
