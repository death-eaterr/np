#include <string>
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"
#include "ns3/netanim-module.h"

using namespace ns3;
int main (int argc, char *argv[])
{
	NodeContainer nodes;
 	nodes.Create (2);
 	
 	PointToPointHelper pointToPoint;
  	pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("500Kbps"));
  	pointToPoint.SetChannelAttribute ("Delay", StringValue ("5ms"));
  	
  	NetDeviceContainer devices;
  	devices = pointToPoint.Install (nodes);
  	
	InternetStackHelper internet;
 	internet.Install (nodes);
 	
	Ipv4AddressHelper ipv4;
 	ipv4.SetBase ("10.1.1.0", "255.255.255.0");
 	Ipv4InterfaceContainer i = ipv4.Assign (devices);
 	
 	BulkSendHelper source ("ns3::TcpSocketFactory",InetSocketAddress (i.GetAddress (1), 9));
 	source.SetAttribute ("MaxBytes", UintegerValue (0));
 	
  	ApplicationContainer sourceApps = source.Install (nodes.Get (0));
  	sourceApps.Start (Seconds (0.0));
  	sourceApps.Stop (Seconds (10.0));
  	
  	PacketSinkHelper sink ("ns3::TcpSocketFactory",InetSocketAddress (Ipv4Address::GetAny (), 9));
  	ApplicationContainer sinkApps = sink.Install (nodes.Get (1));
  	sinkApps.Start (Seconds (0.0));
  	sinkApps.Stop (Seconds (10.0));
  	
  	Simulator::Stop (Seconds (10.0));
  	
	AnimationInterface anim ("fourth.xml"); 
	anim.EnablePacketMetadata(true);
 	Simulator::Run ();
  	Simulator::Destroy ();
  	
}
