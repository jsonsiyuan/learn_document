# LightweightM2M #
	
	官方web:
	https://www.omaspecworks.org
	
	规范已经使用的内容表单：
	http://openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html

	更多相关内容查看github wiki
	https://github.com/OpenMobileAlliance/OMA_LwM2M_for_Developers
## Anjay ##

**一个c库**

	https://avsystem.github.io/Anjay-doc/

## 核心流程 ##

- Bootstrap
- Client Registration
- Device Management and Service Enablement
- Information Reporting


### Bootstrap ###

The Bootstrap Interface is used to provision essential information into the LwM2M Client to enable the LwM2M Client to perform the "Register" operation with one or more LwM2M Servers.

#### Factory Bootstrap ####
#### Bootstrap from Smartcard ####
#### Client Initiated Bootstrap ####
- Step #0: Bootstrap-Request to bootstrap URI
- Step #1: Configure Bootstrap Information
- Step #2: Bootstrap-Finish
- Step #3: Clean-up after successful Bootstrapping

#### Server Initiated Bootstrap ####

Server 可以让client 发起 Client Initiated Bootstrap

note：Objects and Object Instances

### Client Registration Interface ###

The Client Registration Interface is used by a LwM2M Client to register with one or more LwM2M Servers, maintain each registration, and de-register from a LwM2M Server. The registration is based on the Resource Model and Identifiers.

### Device Management and Service Enablement Interface ###

具体的数据交互


## Identifiers and Resources ##

This section defines the identifiers and resource model for the LwM2M Enabler

## Access Control ##

When a LwM2M Client interacts with multiple LwM2M Servers there is a need to determine which operation on a certain
Object or Object Instance is authorized for which LwM2M Server. The Access Control Object has been designed to offer this access management capability.


## 总结 ##

对于资源很紧张的设备，可能适合，因为设备端需要做服务器来适配协议




