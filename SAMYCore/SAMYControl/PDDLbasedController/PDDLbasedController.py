from SAMYControlInterface import *
from abc import ABC
from SAMYControllerBase import SAMYControllerBase
from .PDDLbasedControllerParser import *
import yaml
import queue

class PDDLbasedController(SAMYControllerBase):
    def __init__(self, pathToDomain_, pathToProblem_, pathToPlan_, configurationPath_ = None):
        super().__init__()
        # Configuration of the controller based on PDDL files
        self.pathToDomain = pathToDomain_
        self.pathToPlan = pathToPlan_
        self.pathToProblem = pathToProblem_
        self.configurationPath = configurationPath_
        self.domain, self.problem = self.parseDomainAndProblem()
        self.plan = self.parsePlan() #PDDLPlan 
        self.actionsQueue = queue.Queue() #Queue of actions from PDDL plan that will be executed when possible
        self.internalPDDLactionParameters = ['robot', 'movable'] # parameter types appearing in actions that are only internal for solving the PDDL problem, but not relevant for skills in the SAMYCore
        self.PDDLStateVariables = {} # Array of required PDDL fluents variables that describe the relevant system state for the plan
        self.PDDLStateVariablesNamesAsString = [] # Array of required PDDL fluents variables that describe the relevant system state for the plan expressed with a string (for easier comparing)
        self.controlStateVariables = [] # Array of SAMYCore SystemStatus variables names required by the PDDL Plan that will be tracked (either through configuration file or using naming convention)
        self.controlFluentsStateValues = [] # Array of fluents values describing the system state read from the SAMYCore PDDL_Fluents Information Source
        self.controllerConfiguration = {} # An object that contains the matching between PDDL elements and OPC UA information model of the SAMYCore
        self.orderedActionsByAgent = {}
        self.nextActionToBeRequested = 0 # Keeps track of the last step in the plan requested

        self.setPDDLStateVariables()
        self.setOrderedActionsByAgent()
   
        self.generateConfigurationTemplate()

        self.domain.print()
        self.problem.print()
        self.plan.print()
        pprint.pprint(self.orderedActionsByAgent)

        pprint.pprint(self.PDDLStateVariables)


    def generateConfigurationTemplate(self):
        confTemplate = {}
        confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"] = {}

        confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["AGENTS"] = {}
        for robot in self.plan.robotsActionsRequeriments:
            confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["AGENTS"][robot] = ''

        confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["PARAMETERS(DATABASE_INFOSOURCES)"] = {}
        for parameter in self.plan.paramsRequired:
            if( self.plan.paramsRequired[parameter] not in self.internalPDDLactionParameters ):
                confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["PARAMETERS(DATABASE_INFOSOURCES)"][parameter] = ''

        confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"] = {}
        for action in self.plan.actionsRequired:
            confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"][action] = {}
            confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"][action]["SkillName"] = ""
            for param in self.domain.actions[action].parameters:
                if( not param[1] in self.internalPDDLactionParameters ):
                    varName = param[0].replace("?","")
                    confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"][action][varName + "(" + param[1] + ")"] = ""

        confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["STATE_VARIABLES"] = {}

        for predicateType in self.PDDLStateVariables:
            for arguments in self.PDDLStateVariables[predicateType]:
                confTemplate["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["STATE_VARIABLES"][predicateType + " " + str(arguments)] = ""


        f = open("PDDLbasedController_Configuration_File.txt", "w")
        yaml.dump(confTemplate, f, indent=4)
        f.close()


    def setPDDLStateVariables(self):
         for action in self.plan.actions:
            self.processActionInstanceVariables(action)               
            

    def setOrderedActionsByAgent(self):
         for action in self.plan.actions:
             if( action.instanceParameters[0] in self.orderedActionsByAgent ):
                  self.orderedActionsByAgent[ action.instanceParameters[0] ].append(action)
             else:
                  self.orderedActionsByAgent[ action.instanceParameters[0] ] = [action]
  #          self.processActionInstanceVariables(action)               


    def processActionInstanceVariables(self, pddlActionInstance ):
        for cond in pddlActionInstance.positiveConditions:
            self.processPredicate(pddlActionInstance, cond)
        for cond in pddlActionInstance.negativeConditions:
            self.processPredicate(pddlActionInstance, cond)
        for effect in pddlActionInstance.addEffects:
            self.processPredicate(pddlActionInstance, effect)
        for effect in pddlActionInstance.deleteEffects:
            self.processPredicate(pddlActionInstance, effect)


    def processPredicate(self, pddlActionInstance, argument ):
        agent = pddlActionInstance.instanceParameters[0]
        actionName = pddlActionInstance.name
        actionParameters = pddlActionInstance.parameters

        predicateType = argument[0]
        predicateArguments = argument[1]
        predicateArgumentsInstance = []
        for arg in predicateArguments:
            if( arg[0] == '?' ):
                predicateArgumentsInstance.append( pddlActionInstance.parametersToInstanceParametersMap[arg] )
            else:
                predicateArgumentsInstance.append( arg )

        if( not predicateType in self.PDDLStateVariables ):
            self.PDDLStateVariables[predicateType] = []

        if( not predicateArgumentsInstance in self.PDDLStateVariables[predicateType] ):
            self.PDDLStateVariables[predicateType].append( predicateArgumentsInstance )
            self.PDDLStateVariablesNamesAsString.append(predicateType + " " + str(predicateArgumentsInstance))


    def parseDomainAndProblem(self):
        parser = PDDL_Parser()
        parser.parse_domain(self.pathToDomain)
        domain = PDDLDomain(parser.domain_name, parser.requirements, parser.types, parser.objects, parser.actions, parser.predicates)
        parser.parse_problem(self.pathToProblem)
        problem = PDDLProblem(parser.problem_name, parser.objects, parser.state, parser.positive_goals, parser.negative_goals)
        return domain, problem


    def parsePlan(self):
        parser = PDDLPlanParser(self.pathToPlan, self.domain)
        parser.parse_plan(self.domain)
        return PDDLPlan(parser.PDDLactions, parser.robotsActionsRequeriments, parser.actionsRequired, parser.paramsRequired)


    def generateInformationSourcesFile(self): # Generates the information sources' YAML file that will be used for the variables required by the PDDLController
        informationSources = {}
        informationSources["InformationSourceDescription"] = {}
        informationSources["InformationSourceDescription"]["InformationSourceName"] = "PDDL_Fluents"
        dataTypes = []
        for var in self.controlStateVariables:
           dataTypes.append("Boolean")
        informationSources["InformationSourceDescription"]["DataTypes"] = dataTypes
        pprint.pprint(informationSources)

        f = open("PDDL_Fluent_InformationSource.txt", "w")
        yaml.dump(informationSources, f, indent=4)
        f.close()


    def parseConfigFile(self):
        with open("PDDLbasedController_Configuration_File.txt", "r") as stream:
            self.controllerConfiguration = yaml.safe_load(stream)
            pprint.pprint(self.controllerConfiguration) # DELETE
        for variable in self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["STATE_VARIABLES"]:
            if self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["STATE_VARIABLES"][variable] == "":
                self.controlStateVariables.append(variable)
            else:
                self.controlStateVariables.append(self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["STATE_VARIABLES"][variable])

        for act in self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"]: # Checks that every action param has associated a skill command number
            for par in self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"][act]: # Checks that every action param has associated a skill command number
                if par != 'SkillName':
                    isInteger = self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"][act][par].isdigit()
                #    if( not isInteger ): # Commented for testing purposes
                #        msg = "YOU MUST MAP EACH ACTION PARAMETER TO A COMMAND NUMBER OF THE MATCHING SKILL"
                #        raise RuntimeError(msg)
                else:
                    if self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"][act][par] == '' :
                        self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"][act][par] = act

        self.generateInformationSourcesFile()


    def getControllerStateVariables(self):
        return self.controlStateVariables


    def getNextActionToBeRequested(self):
        return self.plan.PDDLactions[self.nextActionToBeRequested]


    def internalTransitionsThrower(self):
        """
        This function observes events in the SAMYCore
        Converts the standard representation of the controller state into the internal representation
        """
        pass


    def standardStateToInternalState(self, standardState):
        """
        State is an array of numeric and categorical values that represents the state of the system according to the SAMYControllerInterface
        Converts the standard representation of the controller state into the internal representation
        """
        return standardState # We read the info sources corresponding to the PDDL fluents, which is an array of booleans that we can directly use


    def checkActionConditionsSatisfied(self, actionInstance, internalState):
        for cond in actionInstance.positiveConditionsAsString:
            conditionNumber = self.PDDLStateVariablesNamesAsString.index(cond) # It will throw if not found (as it should!)
            if internalState[conditionNumber] == False:
               return False

        for cond in actionInstance.negativeConditionsAsString:
            conditionNumber = self.PDDLStateVariablesNamesAsString.index(cond)
            if internalState[conditionNumber] == True:
               return False
        return True


    def predict(self, internalState):
        """
        Given a state in its internal representation, predicts/computes the next action to perform in the internal representation
        """
   #     plannedAction = self.getNextActionToBeRequested()
        internalSystemAction = []
        for agent in self.orderedActionsByAgent:
           if len( self.orderedActionsByAgent[agent] ) > 0 :
               if self.checkActionConditionsSatisfied(self.orderedActionsByAgent[agent][0], internalState):
                   internalSystemAction.append( self.orderedActionsByAgent[agent].pop(0) )
        return internalSystemAction


    def internalSystemActionToStandardSystemAction(self, internalSystemAction):
        """
        Converts the internal representation of the system action into the standard system action representation (returns a SAMYSystemAction)
        """
        # Array of SAMYAction, one for each agent
        # SAMYAction( agentName, skillName, skillParameters )
        # SAMYActionParameter( commandNumber, 'DataBaseReference', value)
        aux = []
        if( len( internalSystemAction ) > 0 ): # First instance parameters always indicates the agent: internalAction.instanceParameters[0]
            for internalAction in internalSystemAction:
                skillParameters = self.generateSkillParameters( internalAction )
                standardAction = SAMYAction( internalAction.instanceParameters[0], self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"][act][internalAction.name], skillParameters )
                aux.append( standardAction )
            return SAMYSystemAction(aux)
        else:
            return SAMYSystemAction( [ SAMYAction( self.getNextActionToBeRequested().instanceParameters[0], 'pass', [] ) ] )


    def generateSkillParameters(self, internalAction):
        parameters = []
        for param in internalAction.instanceParameters[1:]:
            parameters.append( SAMYActionParameter( self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["ACTIONS"][act][param], 'DataBaseReference', self.controllerConfiguration["CONFIGURATION_FILE_PDDL_BASED_CONTROLLER"]["PARAMETERS"][param]) )
        return parameters









