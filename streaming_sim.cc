#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/netanim-module.h"
using namespace ns3;
int main() {
// =========================
// PARAMETERS (change for runs)
// =========================
std::string dataRate = "5Mbps";
uint32_t packetSize = 1024;
uint32_t intervalMs = 10;
// =========================
NodeContainer nodes;
nodes.Create(2);
PointToPointHelper pointToPoint;
pointToPoint.SetDeviceAttribute("DataRate", StringValue(dataRate));
pointToPoint.SetChannelAttribute("Delay", StringValue("10ms"));
NetDeviceContainer devices = pointToPoint.Install(nodes);
InternetStackHelper stack;
stack.Install(nodes);
Ipv4AddressHelper address;
address.SetBase("10.1.1.0", "255.255.255.0");
Ipv4InterfaceContainer interfaces = address.Assign(devices);
uint16_t port = 9;
// =========================
// SERVER
// =========================
UdpServerHelper server(port);
ApplicationContainer serverApp = server.Install(nodes.Get(1));
serverApp.Start(Seconds(1.0));
serverApp.Stop(Seconds(10.0));
// =========================
// CLIENT (STREAMING)
// =========================
UdpClientHelper client(interfaces.GetAddress(1), port);
client.SetAttribute("MaxPackets", UintegerValue(2000));
client.SetAttribute("Interval", TimeValue(MilliSeconds(intervalMs)));
client.SetAttribute("PacketSize", UintegerValue(packetSize));
ApplicationContainer clientApp = client.Install(nodes.Get(0));
clientApp.Start(Seconds(2.0));
clientApp.Stop(Seconds(10.0));
// =========================
// FLOW MONITOR
// =========================
FlowMonitorHelper flowmon;
Ptr<FlowMonitor> monitor = flowmon.InstallAll();
// =========================
// NETANIM
// =========================
AnimationInterface anim("animation.xml");
anim.SetConstantPosition(nodes.Get(0), 10.0, 20.0);
anim.SetConstantPosition(nodes.Get(1), 50.0, 20.0);
Simulator::Stop(Seconds(10.0));
Simulator::Run();
monitor->CheckForLostPackets();
std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();
for (auto &flow : stats) {
double rxPackets = flow.second.rxPackets;
// =========================
// ✔ CORRECT AVERAGE METRICS
// =========================
double delay = 0.0;
double jitter = 0.0;
if (rxPackets > 0) {
delay = flow.second.delaySum.GetSeconds() / rxPackets;
jitter = flow.second.jitterSum.GetSeconds() / rxPackets;
}
std::cout << "Flow ID: " << flow.first << std::endl;
std::cout << "DataRate: " << dataRate << std::endl;
std::cout << "Packet Size: " << packetSize << std::endl;
std::cout << "Interval: " << intervalMs << " ms" << std::endl;
std::cout << "Average Delay: " << delay << " s" << std::endl;
std::cout << "Average Jitter: " << jitter << " s" << std::endl;
std::cout << "-----------------------------" << std::endl;
}
Simulator::Destroy();
return 0;
}
