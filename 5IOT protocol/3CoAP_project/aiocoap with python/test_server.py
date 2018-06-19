import datetime
import logging
import asyncio
#有问题
import aiocoap.resource as resource
import aiocoap
class TimeResource(resource.Resource):
    def __init__(self):
        super(TimeResource,self).__init__()
    async def render_get(self,request):
        payload=datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S").encode("ascil")
        return aiocoap.Message(code=aiocoap.Code.CONTENT,payload=payload)

logging.basicConfig(level=logging.INFO)
logging.getLogger("coap-server").setLevel(logging.DEBUG)
def main():
    root=resource.Site()
    root.add_resource((".well-known","core"),
                      resource.WKCResource(root.get_resources_as_linkheader()))
    root.add_resource(("time",),TimeResource())
    task=asyncio.Task(aiocoap.Context.create_server_context(root))
    loop = asyncio.get_event_loop()
    loop.run_forever()
if __name__=="__main__":
    main()

