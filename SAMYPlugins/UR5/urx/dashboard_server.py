import logging
import sys
import socket


class Dashboard():
    """ This class establishes a connection to the dashboard interface
        of a UR Robot.
    """

    def __init__(self, host):
        self.logger = logging.getLogger("dashboard")
        self.host = host
        self.port = 29999
        self.dash_socket = None

        try:
            self.dash_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.dash_socket.connect((self.host, self.port))
        except:
            self.logger.error("No connection to Robot!")
            sys.exit()

    def send(self, msg):
        try:
            self.dash_socket.send(msg)
        except:
            print("No connection to Robot (Dash)")

    def stop_program(self):
        """ Stops the running program by sending the stop command to the
            dashboard interface.
        """
        str = "Stop\n"
        msg = str.encode()
        self.send(msg)

    def shutdown(self):
        """ Shutdown the robot by sending the shutdown command to the
            dashboard interface.
        """
        str = "Shutdown\n"
        msg = str.encode()
        self.send(msg)

    def popup(self, text):
        """ Open a popup window on the robot controller and display the text.
            Parameters:
            text: The text that is shown in the popup window.
        """
        str = "popup <" + text + ">\n"
        msg = str.encode()
        self.send(msg)

    def close(self):
        """ Closes the connection to the dashboard interface.
        """
        self.dash_socket.close()
