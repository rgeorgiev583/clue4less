# Design specification

Basically, the idea is to write something which provides a unified framework atop the networking/multiplayer subsystem for serving and playing games in a distributed (i.e. grid- or cluster-like) manner.

From an architectural viewpoint, I plan to separate the plugin into clear-cut components which could theoretically function separately from one another.
More specifically, these are the things I eventually plan (i.e. hope) to implement (of course, I am not sure whether I will manage to complete all of them):
* An abstraction layer atop the networking subsystem which makes sure that transferring objects and performing actions across the network is network-transparent;
* Low-level internal API for the actual grid network implementation so that different distributed infrastructure providers can be used;
* Low-level external API for making the fundamental subsystems of the engine distributed;
* High-level API for on-demand enabling of distributed functionality for user-created objects and functions (or even whole games);
* (this one will be *really* tough to do) Patches for the different subsystems so that they would work with the low-level external API.
