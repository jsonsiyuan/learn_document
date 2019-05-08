# zigbee #

## Stack Architecture ##

- The IEEE 802.15.4 standard defines the two lower layers: the physical (PHY) layer and the medium access control (MAC) sub-layer.
- The ZigBee Alliance builds on this foundation by providing the network (NWK) layer and the framework for the application layer.
- The application layer framework consists of the application support sub-layer (APS) and the ZigBee device objects (ZDO).
- The ZigBee network layer (NWK) supports star, tree, and mesh topologies.


## APPLICATION LAYER ##

- the ZigBee application layer consists of the APS sub-layer, the ZDO (containing the ZDO management plane), and the manufacturer-defined application objects.

### Application Support Sub-Layer ###

- The APS data entity (APSDE) through the APSDE service access point (APSDE-SAP)
- The APS management entity (APSME) through the APSME service access point (APSME-SAP).
- The APSME provides a variety of services to application objects including security services and binding of devices. It also maintains a database of managed objects, known as the APS information base (AIB).

### Application Framework ###

- Up to 254 distinct application objects can be defined, from 1 to 254
-  endpoint 0 is reserved for the data interface to the ZDO
-  endpoint 255 is reserved for the data interface function to broadcast data to all application objects
-  Endpoints 241-254 are assigned by the ZigBee Alliance and shall not be used without approval.The Green Power cluster, if implemented, shall use endpoint 242.

### ZigBee Device Objects ###

 **The ZDO is responsible for the following:**

- Initializing the application support sub-layer (APS), the network layer (NWK), and the Security Ser-vice Provider
- Assembling configuration information from the end applications to determine and implement discov-ery, security management, network management, and binding management