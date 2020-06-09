# DemiGOAP

DemiGOAP is a GOAP planner (Goal Oriented Action Planner) for AI (game or not, it depends if you want a planner or another approach).<br/>
I named the project after the meaning of "Demi": it can means something is not "totally" something or not a "whole" of something.<br/>
This because I spent more time writing the A* algorithim behind, because actually, a GOAP, is simple a pathfinding across nodes.<br/>
Now, the current A* implemented is generic and it uses request made up of anything you want, in this case by world states and actions for the GOAP, but you can use for everything.<br/>
The only thing you have to do is taking care to implement the functions the A* needs.<br/>
Moreover, this GOAP implementation, using a strong A* component, can work with floating cost instead of simple integer cost of the normal GOAP approach, thanks the strong base A*, this is interesting to have very specific balance.<br/>


## Demo

The demo is a simple console text base application, where I made a lumberjack.<br/>
You have to select the number of iterations (working days) and the name of the lumberjack.<br/>
Than the planner will starts: to show the A* behind working good with the planner, I have added oddities in the lumberjack test, such axe can be break or cannot be find, during the different working days.<br/>

This is a screenshot:

<img src="./Screenshots/DemiGOAP.png">


## LICENSE

- Sources:
	- **DemiGOAP**, the main project, is under GPL-3.0


# Build Status

| Platform | Build Status |
|:--------:|:------------:|
| Windows (Visual Studio 2017) | [![Windows Build Status](https://ci.appveyor.com/api/projects/status/github/kabalmcblade/demigoap?branch=master&svg=true)](https://ci.appveyor.com/project/kabalmcblade/demigoap) |
