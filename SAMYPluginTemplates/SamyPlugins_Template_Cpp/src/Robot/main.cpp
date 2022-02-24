
#include "plugin.h"
#include "robot.h"

#include <memory>
#include <signal.h>
#include <signals.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <chrono>

#include "namespace_crcl_generated.h"
#include "types_crcl_generated_handling.h"

#include "spdlog/spdlog.h"


UA_Boolean running = true;
static void stopHandler(int sign) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "received ctrl-c");
    running = false;
}

int main(int argc, char** argv)
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    std::string robotAddress; // address of robot
    std::string samyCoreAddress;
    std::string samyCorePort = "4841";
    std::string robotName;

    if (argc == 4){
        samyCoreAddress = argv[1];
        robotName = argv[2];
        robotAddress = argv[3];
    } else {
        spdlog::error("To few arguments: \n"
                     "\"address of SAMYCore\" \"name of Robot\" "
                     "\"address of robot\"" );
        return -1;
    }

    Signals signals; // Struct of all available signals (all CRCL-commands and signals for skill methods)
    Plugin plugin(samyCoreAddress, samyCorePort, &signals);
    plugin.running = &running;

    // Creating the robot object
    spdlog::info("Connecting to Robot...");
    std::shared_ptr<Robot> robot(new Robot(robotAddress, &signals, &plugin));
    spdlog::info("Connected to Robot");

    // Connect methods to signals
    signals.InitCanon.connect(boost::bind(&Robot::InitCanon, robot, _1));
    signals.EndCanon.connect(boost::bind(&Robot::EndCanon, robot, _1));
    signals.Message.connect(boost::bind(&Robot::Message, robot, _1));
    signals.MoveTo.connect(boost::bind(&Robot::MoveTo, robot, _1));
    signals.MoveScrew.connect(boost::bind(&Robot::MoveScrew, robot, _1));
    signals.MoveThroughTo.connect(boost::bind(&Robot::MoveThroughTo, robot, _1));
    signals.Dwell.connect(boost::bind(&Robot::Dwell, robot, _1));
    signals.ActuateJoints.connect(boost::bind(&Robot::ActuateJoints, robot, _1));
    signals.ConfigureJointReports.connect(boost::bind(&Robot::ConfigureJointReports, robot, _1));
    signals.SetDefaultJointPositionsTolerances.connect(boost::bind(&Robot::SetDefaultJointPositionsTolerances, robot, _1));
    signals.GetStatus.connect(boost::bind(&Robot::GetStatus, robot, _1));
    signals.CloseToolChanger.connect(boost::bind(&Robot::CloseToolChanger, robot, _1));
    signals.OpenToolChanger.connect(boost::bind(&Robot::OpenToolChanger, robot, _1));
    signals.SetRobotParameters.connect(boost::bind(&Robot::SetRobotParameters, robot, _1));
    signals.SetEndeffectorParameters.connect(boost::bind(&Robot::SetEndeffectorParameters, robot, _1));
    signals.SetEndeffector.connect(boost::bind(&Robot::SetEndeffector, robot, _1));
    signals.SetTransAccel.connect(boost::bind(&Robot::SetTransAccel, robot, _1));
    signals.SetTransSpeed.connect(boost::bind(&Robot::SetTransSpeed, robot, _1));
    signals.SetRotAccel.connect(boost::bind(&Robot::SetRotAccel, robot, _1));
    signals.SetRotSpeed.connect(boost::bind(&Robot::SetRotSpeed, robot, _1));
    signals.SetAngleUnits.connect(boost::bind(&Robot::SetAngleUnits, robot, _1));
    signals.SetEndPoseTolerance.connect(boost::bind(&Robot::SetEndPoseTolerance, robot, _1));
    signals.SetForceUnits.connect(boost::bind(&Robot::SetForceUnits, robot, _1));
    signals.SetIntermediatePoseTolerance.connect(boost::bind(&Robot::SetIntermediatePoseTolerance, robot, _1));
    signals.SetLengthUnits.connect(boost::bind(&Robot::SetLengthUnits, robot, _1));
    signals.SetMotionCoordination.connect(boost::bind(&Robot::SetMotionCoordination, robot, _1));
    signals.SetTorqueUnits.connect(boost::bind(&Robot::SetTorqueUnits, robot, _1));
    signals.StopMotion.connect(boost::bind(&Robot::StopMotion, robot, _1));
    signals.ConfigureStatusReport.connect(boost::bind(&Robot::ConfigureStatusReport, robot, _1));
    signals.EnableSensor.connect(boost::bind(&Robot::EnableSensor, robot, _1));
    signals.DisableSensor.connect(boost::bind(&Robot::DisableSensor, robot, _1));
    signals.EnableGripper.connect(boost::bind(&Robot::EnableGripper, robot, _1));
    signals.DisableGripper.connect(boost::bind(&Robot::DisableGripper, robot, _1));
    signals.EnableRobotParameterStatus.connect(boost::bind(&Robot::EnableRobotParameterStatus, robot, _1));
    signals.DisableRobotParameterStatus.connect(boost::bind(&Robot::DisableRobotParameterStatus, robot, _1));

    // Connect to SAMYCore and start listending for commands.
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval = plugin.InitPlugin(robotName);
    spdlog::info("Starting RunClient");
    retval = plugin.RunClient(1000);
    spdlog::info("RunClient has returned");

    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
