using System;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
using System.Diagnostics;

public enum lightstatus
{
    red,
    orange,
    green
}

public class Program {


    static IPAddress ipAddress;
    static IPEndPoint ipEndPoint;
    static Socket listener;
    static Socket socket;
    static TrafficLight[] trafficLights;


    //Setups declaration

    static double[] setup1 = { 1.1, 2.1, 32.2, 35.2, 36.1, 37.1, 37.2 };
    static double[] setup2 = { 5.1, 6.1, 31.1, 31.2, 35.1, 35.2, 37.1, 37.2};
    static double[] setup3 = { 7.1, 8.1, 9.1, 10.1, 31.1, 31.2};
    static double[] setup4 = { 11.1, 12.1, 26.1, 31.1,31.2, 35.1, 35.2, 36.1, 36.2, 38.1, 38.2, 86.1};
    static double[] setup5 = { 6.1, 7.1, 22.0, 28.1, 31.1, 31.2, 32.1, 32.2, 37.1, 37.2, 38.1, 38.2, 88.1};
    static double[] setup6 = { 7.1, 8.1, 28.1, 37.1 ,37.2, 38.1, 38.2, 42, 88.1 };

    static List<double[]> setups = new();

    public static void InitSocket()
    {
       ipAddress = (Dns.Resolve(IPAddress.Any.ToString())).AddressList[2]; ;
       ipEndPoint = new(ipAddress, 11000);
       listener = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);


        Console.WriteLine(ipAddress.MapToIPv4().ToString());

        listener.Bind(ipEndPoint);

        listener.Listen(10);

        socket = listener.Accept();


        socket.ReceiveTimeout = 10000;
        socket.SendTimeout = 5000;

    }

    public static void Tick()
    {
        int currentSetup = -1;
        Stopwatch sw = Stopwatch.StartNew();
        int trafficLightCount = trafficLights.Length;

        TrafficlightInfo[] trafficlightStatusses = new TrafficlightInfo[trafficLights.Length];

        for (int i = 0; i < trafficLights.Length; i++)
        {
            trafficlightStatusses[i] = new TrafficlightInfo()
            {
                id = trafficLights[i].id,
                status = lightstatus.red
            };
        }

        int sendResult;
        int receiveResult;

        string response;


        while (socket.Connected)
        {
            try
            {

                Thread.Sleep(1000);

                byte[] buffer = new byte[8196];

                int bytesRead = socket.Receive(buffer);
                response = System.Text.Encoding.UTF8.GetString(buffer, 0, bytesRead);
                response = response.TrimEnd('\n');
                buffer = new byte[8196];
                Console.WriteLine($"received:  {response}");

                var JsonResponse = JsonSerializer.Deserialize<TrafficInfo[]>(response);

                for (int i = 0; i < trafficLightCount; i++)
                {
                    trafficLights[i].weight = JsonResponse[i].weight;
                    Console.WriteLine($"LightId: {JsonResponse[i].id} Weight: {JsonResponse[i].weight} ");
                }
            }
            catch (Exception e)
            {
                Console.WriteLine($"receiving failed error: {e}");
            }
            try
            {
                //sends the trafficlight data
                for(int i = 0; i < trafficLightCount; i++)
                {
                    trafficlightStatusses[i].status = trafficLights[i].status;
                }

                string message = JsonSerializer.Serialize<TrafficlightInfo[]>(trafficlightStatusses);
                message += '\n';
                byte[] data = System.Text.Encoding.UTF8.GetBytes(message);
                if (socket.Connected)
                {
                    Console.WriteLine($"\n Sending data {message}");
                    sendResult = socket.Send(data);
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

            //if all trafficlights are clear generate new setup
            if (currentSetup == -1)
            {
                int maxWeight = 0;

                for (int i = 0; i < setups.Count; i++)
                {
                    int totalWeight = 0;
                    for (int j = 0; j < setups[i].Length; j++)
                    {
                        totalWeight += trafficLights.First(light => light.id == setups[i][j]).weight;
                    }
                    if (totalWeight > maxWeight)
                    {
                        currentSetup = i;
                    }
                }
            }

            //set trafficlight statusses to correct status using the elapsed time
            for (int i = 0; i < setups[currentSetup].Length; i++)
            {
                TrafficLight light = trafficLights.First(light => light.id == setups[currentSetup][i]);

                if (sw.ElapsedMilliseconds > 3000)
                {
                    light.status = lightstatus.orange;
                }
                else if (sw.ElapsedMilliseconds > 5000)
                {
                    light.status = lightstatus.red;
                    sw.Restart();
                    currentSetup = -1;
                }
                else
                {
                    light.status = lightstatus.green;
                }
            }
        }
        socket.Shutdown(SocketShutdown.Both);
        socket.Close();
    }

    public static void Main()
    {
        double[] lightIds = { 1.1, 2.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1, 11.1, 12.1, 35.1, 35.2, 36.1, 36.2, 37.1, 37.2, 38.1, 38.2, 31.1, 31.2, 32.1, 32.2, 86.1, 26.1, 88.1, 28.1, 22.0, 42.0 };
        trafficLights = new TrafficLight[lightIds.Length];

        for(int i = 0; i < lightIds.Length; i++)
        {
            trafficLights[i] = new TrafficLight();
            trafficLights[i].id = lightIds[i];
            trafficLights[i].weight = 0;
            trafficLights[i].status = lightstatus.red;
        }

        setups.Add(setup1);
        setups.Add(setup2);
        setups.Add(setup3);
        setups.Add(setup4);
        setups.Add(setup5);
        setups.Add(setup6);

        InitSocket();
        Console.WriteLine("connection succeeded");

        Tick();

        

        while (true)
        {
            Console.WriteLine("Connection has been closed do you want to reconnect?   Y/N");
            string retry = Console.ReadLine();
            if (retry == "y" || retry == "Y")
            {
                listener.Listen(10);
                socket = listener.Accept();
                Tick();
            }
            else
            {
                break;
            }
        }


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

public class TrafficLight
{
    public double id { get; set; }

    public int weight { get; set; }

    public lightstatus status { get; set; }
}

