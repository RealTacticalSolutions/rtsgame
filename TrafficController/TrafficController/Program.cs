using System;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
public enum lightstatus
{
    red,
    orange,
    green
}

public class Program {


    public static void Main()
    {
        int setup = 0;

        double[] lightIds = {1.1, 2.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1, 11.1, 12.1, 35.1, 35.2, 36.1, 36.2, 37.1, 37.2, 38.1, 38.2, 31.1, 31.2,32.1, 32.2, 86.1, 26.1, 88.1, 28.1, 22.0};

        TrafficlightInfo[] trafficlightInfos = new TrafficlightInfo[lightIds.Length];

        for (int i = 0; i < lightIds.Length; i++)
        {
            trafficlightInfos[i] = new TrafficlightInfo()
            {
                id = lightIds[i],
                status = lightstatus.red
            };
        }

        IPAddress ipAddress = IPAddress.Parse("141.252.221.5");
        IPEndPoint ipEndPoint = new(ipAddress, 11000);

        Socket listener = new Socket(ipEndPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

        listener.Bind(ipEndPoint);

        listener.Listen(10);

        int sendResult;
        int receiveResult;

        string response;

        Socket socket = listener.Accept();

        socket.ReceiveTimeout = 10000;
        socket.SendTimeout = 5000;

        Console.WriteLine("connection succeeded");

        while (socket.Connected)
        {
            try
            {

                Thread.Sleep(1000);

                byte[] buffer = new byte[2048];

                int bytesRead = socket.Receive(buffer);
                response = System.Text.Encoding.UTF8.GetString(buffer, 0, bytesRead);
                Console.WriteLine($"received:  {response}");

                TrafficInfo[]? JsonResponse = JsonSerializer.Deserialize<TrafficInfo[]>(response);

                foreach (TrafficInfo trafficInfo in JsonResponse)
                {
                    Console.WriteLine($"LightId: {trafficInfo.id} Weight: {trafficInfo.weight} ");

                }
            }
            catch(Exception e)
            {
                Console.WriteLine($"receiving failed error: {e}");
            }
            try
            {

                string message = JsonSerializer.Serialize<TrafficlightInfo[]>(trafficlightInfos);
                message += '\n';
                byte[] data = System.Text.Encoding.UTF8.GetBytes(message);
                if (socket.Connected)
                {
                    Console.WriteLine($"Sending data {message}");
                    sendResult = socket.Send(data);
                }

                foreach (TrafficlightInfo info in trafficlightInfos)
                {
                    info.status = lightstatus.red;
                }

                switch (setup) {
                    case 0:
                        trafficlightInfos[0].status = lightstatus.green;
                        trafficlightInfos[1].status = lightstatus.green;
                        trafficlightInfos[10].status = lightstatus.green;
                        setup = 1;
                        break;
                    case 1:
                        trafficlightInfos[2].status = lightstatus.green;
                        trafficlightInfos[3].status = lightstatus.green;
                        setup = 2;
                        break;
                    case 2:
                        trafficlightInfos[4].status = lightstatus.green;
                        trafficlightInfos[5].status = lightstatus.green;
                        trafficlightInfos[6].status = lightstatus.green;
                        setup = 3;
                        break;
                    case 3:
                        trafficlightInfos[7].status = lightstatus.green;
                        trafficlightInfos[8].status = lightstatus.green;
                        trafficlightInfos[9].status = lightstatus.green;
                        setup = 0;
                        break;
                }
            }
            catch (Exception e)
            {
                if (e is SocketException socketException && socketException.SocketErrorCode == SocketError.ConnectionAborted)
                {

                }
                Console.WriteLine("Sending failed");
                Console.WriteLine("ERROR: " + e);

            }
        }

        Console.ReadLine();

        socket.Shutdown(SocketShutdown.Both);
        socket.Close();
    }
}
public class TrafficInfo
{
    public double id { get; set; }

    public int weight { get; set;  }
}

public class TrafficlightInfo
{
    public double id { get; set; }

    public lightstatus status { get; set; }
}

