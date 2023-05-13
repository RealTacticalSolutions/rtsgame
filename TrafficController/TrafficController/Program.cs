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
    static Stopwatch bikeTimer = new Stopwatch();

    static bool enableTimer = false;
    static int maxTime = 120;

    //Setups declaration

    static double[] setup1 = { 1.1, 2.1, 32.2, 35.2, 36.1, 37.1, 37.2 };
    static double[] setup2 = { 5.1, 6.1, 31.1, 31.2, 35.1, 35.2, 37.1, 37.2};
    static double[] setup3 = { 7.1, 8.1, 9.1, 10.1, 31.1, 31.2};
    static double[] setup4 = { 11.1, 12.1, 26.1, 31.1,31.2, 35.1, 35.2, 36.1, 36.2, 38.1, 38.2, 86.1};
    static double[] setup5 = { 6.1, 7.1, 22.0, 28.1, 31.1, 31.2, 32.1, 32.2, 37.1, 37.2, 38.1, 38.2, 88.1};
    static double[] setup6 = { 7.1, 8.1, 28.1, 37.1 ,37.2, 38.1, 38.2, 42.0, 88.1 };

    static double[] trainSetup1 = { 22.0 ,26.1, 28.1, 31.1, 31.2, 32.1, 32.2, 35.1, 35.2, 36.1, 36.2, 37.1, 37.2, 38.1, 38.2, 86.1, 88.1};

    static List<double[]> setups = new();
    static int oldSetup = -1;

    public static void InitSocket()
    {
       ipAddress = (Dns.Resolve(IPAddress.Any.ToString())).AddressList[3];
       ipEndPoint = new(ipAddress, 11000);
       listener = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);


        Console.WriteLine(ipAddress.MapToIPv4().ToString());

        listener.Bind(ipEndPoint);

        listener.Listen(10);

        socket = listener.Accept();


        socket.ReceiveTimeout = 10000;
        socket.SendTimeout = 5000;

    }

    public static void sendTrafficLightInfo()
    {

    }

    public static void setLights(int setupIndex, lightstatus lightstatus)
    {
        for (int i = 0; i < setups[setupIndex].Length; i++)
        {
            TrafficLight light = trafficLights.First(light => light.id == setups[setupIndex][i]);

            light.status = lightstatus;
        }

        if (setupIndex == 6)
        {
            bikeTimer.Restart();
        }
    }

    public static int getBestSetup()
    {
        int bestSetup = 0;
        int maxWeight = 0;
        if ((int)bikeTimer.Elapsed.TotalSeconds > maxTime)
        {
            return 6;
        }

        if (trafficLights.First(light => light.id == 42).weight >= 1)
        {
            return 5;
        }

        for (int i = 0; i < setups.Count; i++)
        {
            int totalWeight = 0;
            for (int j = 0; j < setups[i].Length; j++)
            {
                totalWeight += trafficLights.First(light => light.id == setups[i][j]).weight;
            }
            if (i == 6)
            {
                totalWeight = totalWeight / 2;
            }
            if (totalWeight >= maxWeight)
            {
                maxWeight = totalWeight;
                bestSetup = i;
            }
        }
        return bestSetup;
    }

    public static void Tick()
    {
        int currentSetup = -1;
        Stopwatch sw = Stopwatch.StartNew();
        Stopwatch trainStopWatch = new Stopwatch();
        bikeTimer.Start();
        bool trainPassed = false;
        bool reset = true;

        double activeTrainlightId = 0;
        int trafficLightCount = trafficLights.Length;

        TrafficlightInfo[] trafficlightStatusses = new TrafficlightInfo[trafficLights.Length];

        Timer timer = new();
        timer.id = 69.0;
        timer.status = lightstatus.green;
        timer.remainingTime = maxTime;

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
            //try receiving data from simulator
            try
            {

                byte[] buffer = new byte[8196];

                int bytesRead = socket.Receive(buffer);
                response = System.Text.Encoding.UTF8.GetString(buffer, 0, bytesRead);
                response = response.TrimEnd('\n');
                buffer = new byte[8196];
                
                var JsonResponse = JsonSerializer.Deserialize<TrafficInfo[]>(response);

                for (int i = 0; i < trafficLightCount; i++)
                {
                    trafficLights[i].weight = JsonResponse.First(light => light.id == trafficLights[i].id).weight;
                    Console.WriteLine($"LightId: {JsonResponse[i].id} Weight: {JsonResponse[i].weight} ");
                }
            }
            catch (Exception e)
            {
                Console.WriteLine($"receiving failed error: {e}");
            }
            //try sending data to simulator
            try
            {
                if (!((int)bikeTimer.Elapsed.TotalSeconds > maxTime))
                {
                    timer.remainingTime = maxTime - (int)bikeTimer.Elapsed.TotalSeconds;
                }        

                //sends the trafficlight data
                for(int i = 0; i < trafficLightCount; i++)
                {
                    trafficlightStatusses[i].status = trafficLights[i].status;
                }

                string message;

                if (enableTimer)
                {

                    ControllerInfo controllerInfo = new ControllerInfo();
                    controllerInfo.trafficLights = trafficlightStatusses;
                    controllerInfo.timer = timer;

                    message = JsonSerializer.Serialize<ControllerInfo>(controllerInfo);
                    message = message.Insert(message.IndexOf("69") + 2, ".0");
                }
                else
                {
                    message = JsonSerializer.Serialize<TrafficlightInfo[]>(trafficlightStatusses);
                }
               
                message += '\n';
                message = message.Insert(message.IndexOf("22") + 2,".0");
                message = message.Insert(message.IndexOf("42") + 2, ".0");
                message = message.Insert(message.IndexOf("99") + 2, ".0");
                message = message.Insert(message.IndexOf("152") + 3, ".0");
                message = message.Insert(message.IndexOf("154") + 3, ".0");
                message = message.Insert(message.IndexOf("160") + 3, ".0");
                byte[] data = System.Text.Encoding.UTF8.GetBytes(message);
                if (socket.Connected)
                {
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
                currentSetup = getBestSetup();

                if (currentSetup == 5)
                {
                    bikeTimer.Stop();
                    timer.status = lightstatus.orange;
                }
                else
                {
                    timer.status = lightstatus.green;
                    bikeTimer.Start();
                }
            }

            //check for active trainLights
            if(trafficLights.First(light => light.id == 152).weight > 0)
            {
                activeTrainlightId = 152;
            }
            else if (trafficLights.First(light => light.id == 154).weight > 0)
            {
                activeTrainlightId = 154;
            }
            else if (trafficLights.First(light => light.id == 160).weight > 0)
            {
                activeTrainlightId = 160;
            }

            //train logic
            if (activeTrainlightId > 0 || trainPassed)
            {
                TrafficLight activeTrainLight = trafficLights.First(light => light.id == activeTrainlightId);

                if (!trainStopWatch.IsRunning)
                {
                    trainStopWatch.Start();
                }

                TrafficLight railWayLight = trafficLights.First(light => light.id == 99);

                if (trainPassed)
                {
                    if (reset)
                    {
                        trainStopWatch.Restart();
                        reset = false;
                    }

                    switch (trainStopWatch.ElapsedMilliseconds)
                    {
                        case < 12000:
                            activeTrainLight.status = lightstatus.red;
                            break;
                        case < 17000:
                            setLights(6, lightstatus.orange);
                            railWayLight.status = lightstatus.orange;
                            break;
                        case > 17000:
                            setLights(6, lightstatus.red);
                            railWayLight.status &= lightstatus.green;
                            trainStopWatch.Reset();
                            trainPassed = false;
                            activeTrainlightId = 0;
                            break;
                    }

                }
                else
                {
                    switch (trainStopWatch.ElapsedMilliseconds)
                    {
                        case < 3000:
                            setLights(currentSetup, lightstatus.orange);
                            break;
                        case < 6000:
                            setLights(currentSetup, lightstatus.red);
                            break;
                        case < 10000:
                            setLights(6, lightstatus.green);
                            railWayLight.status = lightstatus.orange;
                            break;
                        case < 15000:
                            railWayLight.status = lightstatus.red;
                            break;
                        case < 27000:
                            activeTrainLight.status = lightstatus.green;
                            break;
                        case > 27000:
                            trainPassed = true;
                            break;

                    };
                    reset = true;
                }
            }
            else
            {
                //set trafficlight statusses to correct status using the elapsed time
                if (sw.ElapsedMilliseconds > 13000)
                {
                    Console.Clear();
                    sw.Restart();
                    currentSetup = -1;
                }
                else if (sw.ElapsedMilliseconds > 10000)
                {
                    setLights(currentSetup, lightstatus.red);
                }
                else if (sw.ElapsedMilliseconds > 6000)
                {
                    setLights(currentSetup, lightstatus.orange);
                }
                else
                {
                    setLights(currentSetup, lightstatus.green);
                }
            }


            Thread.Sleep(500);

        }
        socket.Shutdown(SocketShutdown.Both);
        socket.Close();
    }

    public static void Main()
    {
        double[] lightIds = { 1.1, 2.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1, 11.1, 12.1, 35.1, 35.2, 36.1, 36.2, 37.1, 37.2, 38.1, 38.2, 31.1, 31.2, 32.1, 32.2, 86.1, 26.1, 88.1, 28.1, 22.0, 42.0, 152.0, 154.0, 160.0, 99.0 };
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
        setups.Add(trainSetup1);

        Console.Write("do you want to enable timer? y/n");
        string result = Console.ReadLine();
        if (result.ToLower() == "y")
        {
            enableTimer = true;
        }
        InitSocket();
        Console.WriteLine("connection succeeded");

        Tick();

        

        while (true)
        {
            Console.WriteLine("Connection has been closed do you want to reconnect?   Y/N");
            //string retry = Console.ReadLine();

            Thread.Sleep(500);
            listener.Listen(10);
            socket = listener.Accept();
            Tick();
        }


    }
}

public class ControllerInfo {
    public TrafficlightInfo[] trafficLights { get; set; }

    public Timer timer { get; set; }
}

public class Timer
{
    public double id { get; set; }

    public lightstatus status { get; set; }

    public int remainingTime { get; set; }
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

