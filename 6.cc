#include "ns3/netanim-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

int main(int argc, char* argv[])
{
	Time::SetResolution(Time::NS);
	
	NodeContainer nodes;
	nodes.Create(2);
	
	PointToPointHelper p;
	p.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
	p.SetChannelAttribute("Delay", StringValue("2ms"));
	
	NetDeviceContainer nd;
	nd = p.Install(nodes);
	
	InternetStackHelper tcp;
	tcp.Install(nodes);
	
	Ipv4AddressHelper add;
	add.SetBase("10.1.1.0", "255.255.255.0");
	
	Ipv4InterfaceContainer interface = add.Assign(nd);
	
	UdpEchoServerHelper es(9);
	ApplicationContainer ap = es.Install(nodes.Get(1));
	
	ap.Start(Seconds(1.0));
	ap.Stop(Seconds(10.0));
	
	UdpEchoClientHelper ec(interface.GetAddress(1), 9);
	ec.SetAttribute("MaxPackets", UintegerValue(1));
	ec.SetAttribute("Interval", TimeValue(Seconds(1.0)));
	ec.SetAttribute("PacketSize", UintegerValue(1024));
	
	ApplicationContainer app = ec.Install(nodes.Get(0));	
	app.Start(Seconds(2.0));
	app.Stop(Seconds(10.0));
	
	AnimationInterface anim("first_first.xml");
	Simulator::Run();
	Simulator::Destroy();
	
	return 0;
}
