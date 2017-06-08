# Design specification

Basically, the idea is to write something which provides a unified framework atop the networking/multiplayer subsystem for serving and playing games in a distributed (i.e. grid- or cluster-like) manner.

From an architectural viewpoint, I plan to separate the plugin into clear-cut components which could theoretically function separately from one another.
More specifically, these are the ones I eventually plan to implement (it is not guaranteed that I will manage to complete all of them):
* **Low-level backend API**: for the actual distributed network implementation so that different distributed infrastructure providers can be used;
* **Low-level frontend API**: for making the various subsystems of the engine distributed (this would mean patching the different subsystems);
* **High-level API**: for enabling of distributed functionality for the various objects and functions (or even whole games).  This layer would be positioned atop everything and will make sure that transferring objects and performing actions across the network is network-transparent.
* **Network abstraction layer**: a high-level interface that provides network transparency.

To be honest, I would consider it a success to only *partially* implement any one of these.

## Low-level backend API
It is designed so that it could use external libraries for the whole implementation (or UE-specific ones or ones actually used in UE).
The main elements of the API:
* `StreamTransport`:  the default implementation would probably the [internal low-level TCP socket API in Unreal](https://wiki.unrealengine.com/TCP_Socket_Listener,_Receive_Binary_Data_From_an_IP/Port_Into_UE4,_%28Full_Code_Sample%29)):  could theoretically use any stream-oriented protocol, not only TCP;
* `DatagramTransport`"  the default implementation would probably the [internal low-level UDP socket API in Unreal](https://wiki.unrealengine.com/UDP_Socket_Sender_Receiver_From_One_UE4_Instance_To_Another)):  could theoretically use any datagram-oriented protocol, not only UDP;
* `ChannelConnection`:  implementation of a message-oriented protocol;
* `Auth`:  authentication protocol between nodes;
* `DistributedHash`:  for various things;
* `Replicator`:  would take care of replications of objects.  Makes sense because it would mainly handle batch replications;
* `ObjectPool`:  would probably be a wrapper over the DistributedHash for accessing objects located in various nodes;
* `Node`:  abstract representation of a node in the distributed system;
* `Grid`:  abstract representation of the whole distributed network, including all dependencies between the various nodes;
* `TreeGrid`:  a rooted hierarchical grid;
* `RingGrid`:  a grid whose nodes are with equal priority;
* `CompositeGrid`:  a grid which is composed of grids of different types;
* `RootNode`:  the node with the highest priority;
* `CustomNode`:  a node with a custom-defined priority;
* ... and other kinds of nodes.


## Low-level frontend API

It will consist of configuration files on each node (i.e. peer) which will specify the capabilities of the node, and will be instance-specific:
* `NodeSystem`: defines which subsystem(s) will the node be responsible for;
* `NodeSpecs`: defines the computational abilities of the node (which are to be obtained from hardware benchmarks, for which a separate/external tool would be extremely useful):  they would be expressed in terms of the approximate maximum numbers of objects which could be created from classes of certain complexities.
* `NodeStorage`: defines the different levels of persistence.
* `NodeRole`: defines descriptions of conditional replication rules which explain when exactly an object of a certain type should be replicated on the current node.  There will be filters for objects of certain types: how much of them are allowed to be stored, also the complexity and generationality of the objects, etc.;
* `NodeAuthority`: the authority of the node: what is it allowed to modify, etc; will map to UE authority.


## High-level API

This will be used by the people who create modules and plugins.  It will mainly extend various classes and also *heavily* use reflection:
* It will include wrappers for the different kinds of objects (which could be generated using reflection).  These wrappers would add some logic which enables the object to be distributed: for example, a measure of the complexity of the object (time and space), generationality of the object (how many instances of it are expected to be created during the duration of the game), quantifiers for how frequently the object is accessed from certain other objects, lifetime of the object (how long it would be kept in memory), peristentce of the object (whether it will survive across different instances of the game), etc;
** Task:  has some priority and computational load defined; different types of tasks would be mapped to different behaviours in UI.


## Network abstraction layer

This will actually include (sort of) an implementation of P2P networking, and is not required for the other components to work.
It will actually provide a really high-level interface to the game developer that hides from him the various network-related tasks such as caring about replication (and actually the whole networking subsystem).

Actually it would include wrappers for the classes in UE which have network-dependent behaviour which makes them work network-transparently.
