Imports System.IO.Ports

Module Program
    Sub Main()
        ' Configure the serial port
        Dim portName As String = "COM3" ' Replace with your actual COM port
        Dim baudRate As Integer = 9600

        Using serialPort As New SerialPort(portName, baudRate)
            Try
                ' Open the serial port
                serialPort.Open()
                Console.WriteLine($"Connected to {portName} at {baudRate} baud.")

                While True
                    ' Prompt the user for a command
                    Console.WriteLine("Enter command ('ON' or 'OFF'):")
                    Dim command As String = Console.ReadLine()

                    ' Send the command to the Arduino
                    serialPort.WriteLine(command)

                    ' Wait for a response from the Arduino
                    If serialPort.BytesToRead > 0 Then
                        Dim response As String = serialPort.ReadLine().Trim()
                        Console.WriteLine($"Response: {response}")
                    End If
                End While
            Catch ex As Exception
                Console.WriteLine($"Error: {ex.Message}")
            End Try
        End Using
    End Sub
End Module
