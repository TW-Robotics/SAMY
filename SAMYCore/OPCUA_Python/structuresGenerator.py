from opcua.common.structures import StructGenerator

def generateCRCLStructures():
    xmlpath = "CRCL.Types.bsd"
    c = StructGenerator()
    c.make_model_from_file(xmlpath)
    struct_dict = c.save_and_import("structures.py")


generateCRCLStructures()


