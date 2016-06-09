# Design specification

Basically, the idea is to write something which provides a unified framework atop the networking/multiplayer subsystem for serving and playing games in a distributed (i.e. grid- or cluster-like) manner.

From an architectural viewpoint, I plan to separate the plugin into clear-cut components which could theoretically function separately from one another.
More specifically, these are the things I eventually plan (i.e. hope) to implement (of course, I am not sure whether I will manage to complete all of them):
* Low-level backend API for the actual distributed network implementation so that different distributed infrastructure providers can be used;
* Low-level frontend API for making the various subsystems of the engine distributed;
* High-level API for enabling of distributed functionality for the various objects and functions (or even whole games);
* An abstraction layer atop everything which makes sure that transferring objects and performing actions across the network is network-transparent;
* (this one will be *really* tough to do) Patches for the different subsystems so that they would work with the low-level external API.

## Low-level backend API
It is designed so that it could use external libraries for the whole implementation (or UE-specific ones or ones actually used in UE).
The main elements of the API:
* StreamConnection (the default implementation would probably the [internal low-level TCP socket API in Unreal](https://wiki.unrealengine.com/TCP_Socket_Listener,_Receive_Binary_Data_From_an_IP/Port_Into_UE4,_%28Full_Code_Sample%29)):  could theoretically use any stream-oriented protocol, not only TCP;
* DatagramConnection (the default implementation would probably the [internal low-level UDP socket API in Unreal](https://wiki.unrealengine.com/UDP_Socket_Sender_Receiver_From_One_UE4_Instance_To_Another)):  could theoretically use any datagram-oriented protocol, not only UDP;
* DistributedHash
* Node:  abstract representation of a node in the distributed system;
* Grid:  abstract representation of the whole distributed network, including all dependencies between the various nodes;
* TreeGrid:  a rooted hierarchical grid;
* RingGrid:  a grid which has all nodes with equal priority;
* CompositeGrid:  A grid which is composed of grids of different types;
* RootNode:  the node with the highest priority;
* Node:  a node with custom-defined priority.

## Low-level frontend API

It will work with configuration files on each node (i.e. peer) which will specify the capabilities of the node:
* which subsystem(s) will the node be responsible for;
* the computational ablities of the node (which are to be obtained from hardware benchmarks, for which a tool could also  ):  they would be expressed in the terms of approximate maximum numbers of objects which could be created from the different classes.
* descriptions of conditional replication rules which explain when exactly an object of a certain type should be replicated on the current node.

## High-level API

This will be used by the people who create modules and plugins.

* Wrappers for the different objects which could be generated using reflection;
* Task:  has some priority and computational load defined;
* Different types of tasks which could be mapped to behaviours in UE.

## Network abstraction layer

This will actually include (sort of) an implementation of P2P networking, and is not required for the other components to work.
It will actually provide a really high-level interface to the game developer that hides from him the various network-related tasks such as caring about replication.