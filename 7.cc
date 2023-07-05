#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main (int argc, char *argv[])
{
	NodeContainer pnodes;
	pnodes.Create(2);
	
	NodeContainer cnodes;
	cnodes.Add(pnodes.Get(1));
	cnodes.Create(3);
	
	PointToPointHelper p;
	p.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
	p.SetChannelAttribute("Delay",StringValue("2ms"));
	
	CsmaHelper c;
	c.SetDeviceAttribute("Mtu",UintegerValue(1024));
	c.SetChannelAttribute("DataRate",StringValue("5Mbps"));
	c.SetChannelAttribute("Delay",StringValue("2ms"));
	
	NetDeviceContainer pdevices = p.Install(pnodes);
	NetDeviceContainer cdevices = c.Install(cnodes);
	
	InternetStackHelper stack;
	stack.Install(pnodes.Get(0));
	stack.Install(cnodes);
	
	Ipv4AddressHelper add;
	add.SetBase("10.1.1.0","255.255.255.0");
	Ipv4InterfaceContainer pinterface = add.Assign(pdevices);
	
	add.SetBase("10.1.2.0","255.255.255.0");
	Ipv4InterfaceContainer cinterface = add.Assign(cdevices);
	
	UdpEchoServerHelper es (9);
	
	ApplicationContainer ap = es.Install(cnodes.Get(3));
	ap.Start (Seconds (1.0));
  	ap.Stop (Seconds (10.0));
  	
  	UdpEchoClientHelper ec(cinterface.GetAddress(3),9);
  	ec.SetAttribute ("MaxPackets", UintegerValue (1));
  	ec.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  	ec.SetAttribute ("PacketSize", UintegerValue (1024));
	
	ApplicationContainer clientApps = ec.Install (pnodes.Get (0));
  	clientApps.Start (Seconds (2.0));
  	clientApps.Stop (Seconds (10.0));
  	
  	Ipv4GlobalRoutingHelper::PopulateRoutingTables();
  	p.EnablePcapAll("second");
  	c.EnablePcap("second", cdevices.Get(1),true);
  	
  	AnimationInterface anim ("third.xml");
	Simulator::Run ();
  	Simulator::Destroy ();
  	return 0;
	
}
