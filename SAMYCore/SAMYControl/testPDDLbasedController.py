import PDDLbasedController.PDDLbasedController as PDDLbasedController
import SAMYControlInterface

controller = PDDLbasedController.PDDLbasedController('/home/jbg/Desktop/SAMY/SAMYControl/minUseCase/PDDL/domain-min-strips2.pddl', '/home/jbg/Desktop/SAMY/SAMYControl/minUseCase/PDDL/problem-min-strips2-1.pddl', './plan-min-strips2-1-manual.plan')

controller.parseConfigFile()

#controlInterface = SAMYControlInterface.SAMYControlInterface( 'opc.tcp://localhost:4840/', controller.controlStateVariables, controller.standardControlCallback)
#controlInterface.startSystemControl(100)
