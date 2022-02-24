import sys
sys.path.insert(0, "..")

try:
    from IPython import embed
except ImportError:
    import code

    def embed():
        vars = globals()
        vars.update(locals())
        shell = code.InteractiveConsole(vars)
        shell.interact()


from opcua import Client
from opcua import ua

def get_namespaces(client):
    namespaces = {}
    root_node = client.get_root_node()
    browse_path = ["0:Objects", "0:Server", "0:NamespaceArray"]
    namespaceArrayNode = root_node.get_child(browse_path)
    namespacesValue = namespaceArrayNode.get_value()
    for i, namespace in enumerate(namespacesValue):
        namespaces[namespace] = i
    return namespaces

def resetRobotSkills(opcua_core_client, robot_node):
        skills_node = robot_node.get_child("5:Skills")
        skill_list = skills_node.get_children()
        for skill_node in skill_list:
            skill_node.call_method("0:Reset")

class SubHandler(object):

    """
    Subscription Handler. To receive events from server for a subscription
    data_change and event methods are called directly from receiving thread.
    Do not do expensive, slow or network operation there. Create another
    thread if you need to do such a thing
    """
    def event_notification(self, event):
        print("New event recived: ", event)
        print( type(event) )

if __name__ == "__main__":

    client = Client("opc.tcp://localhost:4840/")
    # client = Client("opc.tcp://admin@localhost:4840/freeopcua/server/") #connect using a user
    try:
        client.connect()

        root = client.get_root_node()
        # Client has a few methods to get proxy to UA nodes that should always be in address space such as Root or Objects
        robotNode = client.get_node("ns=8;i=16428")
        robotNodeUppest = client.get_node("ns=8;i=15001")

     #   resetRobotSkills(client, robotNode)

        namespaces = get_namespaces(client)
        nsFortissDI = namespaces["https://fortiss.org/UA/DI/"]
        skillTransitionEventBrowsePath = str(nsFortissDI) + ':SkillTransitionEventType'
        samy_event = client.get_root_node().get_child(["0:Types","0:EventTypes","0:BaseEventType","0:TransitionEventType","0:ProgramTransitionEventType", skillTransitionEventBrowsePath])

        msclt = SubHandler()
        sub = client.create_subscription(100, msclt)
        handle = sub.subscribe_events(robotNodeUppest, samy_event)
        resetRobotSkills(client, robotNode)

        embed()
        sub.unsubscribe(handle)
        sub.delete()
    finally:
        client.disconnect()
