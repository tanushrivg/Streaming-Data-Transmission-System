# Streaming Data Transmission System

A network simulation project built using **C++** and **NS-3**, modeling a real-time UDP-based client-server streaming architecture. The system analyzes key Quality of Service (QoS) metrics — **delay** and **jitter** — under varying network conditions, simulating scenarios relevant to live broadcast and IPTV streaming pipelines.

---

## 🎯 Objectives

- Simulate a streaming data transmission system using C++ and NS-3
- Model a UDP client-server architecture over a point-to-point network link
- Measure and analyze **average delay** and **average jitter** under different traffic conditions
- Understand the impact of network congestion on real-time streaming quality

---

## 🛠️ Tools & Technologies

| Tool | Purpose |
|---|---|
| NS-3 Simulator | Network simulation environment |
| C++ | Simulation logic and implementation |
| Ubuntu (Virtual Machine) | Development and execution environment |
| FlowMonitor | QoS metric extraction (delay, jitter) |
| NetAnim | Packet transmission visualization |
| Microsoft Excel | Data recording and graph plotting |

---

## 🏗️ System Architecture

```
[ Sender Node ] ──── Point-to-Point Link ──── [ Receiver Node ]
  UDP Client                                      UDP Server
  (Streaming Traffic)                          (Packet Collection)
                         ↓
                    FlowMonitor
               (Delay & Jitter Measurement)
```

- Two nodes connected via a configurable point-to-point link
- UDP client sends packets continuously at fixed intervals to simulate streaming
- FlowMonitor captures per-packet timing data for QoS analysis
- NetAnim generates an XML animation file for visual inspection

---

## ⚙️ Key Parameters

| Parameter | Values Tested |
|---|---|
| Data Rate | 5 Mbps, 10 Mbps |
| Packet Size | 512 bytes, 1024 bytes |
| Packet Interval | 1 ms, 10 ms |
| Link Delay | 10 ms (fixed) |
| Simulation Duration | 10 seconds |

---

## 📊 Results Summary

| Run | Data Rate | Packet Size | Interval | Avg Delay (s) | Avg Jitter (s) |
|---|---|---|---|---|---|
| 1 | 5 Mbps | 1024 B | 10 ms | 0.011686 | 0.000000 |
| 2 | 5 Mbps | 1024 B | 1 ms | 0.580994 | 0.000648 |
| 3 | 10 Mbps | 1024 B | 1 ms | 0.010843 | 0.000000 |
| 4 | 5 Mbps | 512 B | 1 ms | 0.010867 | 0.000000 |

### Key Findings
- Reducing packet interval from 10 ms → 1 ms caused **~50x increase in delay** due to network congestion
- Doubling data rate from 5 Mbps → 10 Mbps restored delay to baseline (~0.011s)
- Reducing packet size from 1024 B → 512 B achieved equivalent delay improvement at same bandwidth
- Jitter only appeared under high traffic load (Run 2), confirming congestion-driven instability

---

## 🚀 How to Run

### Prerequisites
- Ubuntu 20.04 or later (native or VM)
- NS-3 installed ([NS-3 Installation Guide](https://www.nsnam.org/wiki/Installation))

### Steps

1. Clone this repository:
```bash
git clone https://github.com/your-username/streaming-data-transmission-ns3.git
cd streaming-data-transmission-ns3
```

2. Copy the simulation script to your NS-3 scratch folder:
```bash
cp streaming_sim.cc /path/to/ns-3/scratch/
```

3. Navigate to your NS-3 directory and run:
```bash
cd /path/to/ns-3
./ns3 run scratch/streaming_sim
```

4. To change parameters (data rate, packet size, interval), edit these lines in `streaming_sim.cc`:
```cpp
std::string dataRate = "5Mbps";   // Change to "10Mbps" etc.
uint32_t packetSize  = 1024;      // Change to 512 etc.
uint32_t intervalMs  = 10;        // Change to 1 etc.
```

5. View animation output using NetAnim:
```bash
./NetAnim animation.xml
```

---

## 📁 Repository Structure

```
streaming-data-transmission-ns3/
│
├── streaming_sim.cc       # Main NS-3 simulation script (C++)
├── animation.xml          # NetAnim output (generated on run)
├── results/
│   ├── results_table.xlsx # Recorded delay & jitter values
│   ├── delay_vs_interval.png
│   └── jitter_vs_interval.png
└── README.md
```

---

## 📚 References

1. Kurose & Ross — *Computer Networking: A Top-Down Approach*
2. Tanenbaum — *Computer Networks*
3. Forouzan — *Data Communications and Networking*
4. [NS-3 Official Documentation](https://www.nsnam.org/docs/)
5. UDP RFC 768, IP RFC 791
6. [FlowMonitor NS-3 Docs](https://www.nsnam.org/docs/models/html/flow-monitor.html)
7. [NetAnim Documentation](https://www.nsnam.org/wiki/NetAnim)

---
