# Load Data Analysis with Husky A200

## Project Description

This project describes the execution of a load data analysis using the Husky A200 robot on three different rough roads. Instead of conducting a simulation, real experiments were performed to obtain an accurate assessment of the robot's loads and fatigue properties.

## Table of Contents

1. [Project Objectives](#project-objectives)
2. [Hardware and Software](#hardware-and-software)
3. [Experiments](#experiments)
4. [Data Analysis](#data-analysis)
5. [Results](#results)
6. [Conclusion](#conclusion)
7. [References](#references)

## Project Objectives

- Identify and construct three rough roads
- Perform reference scans with a RoadLoad system
- Apply the umx_driver um6 to the Husky A200
- Conduct driving tests on the rough roads
- Analyze the collected data using the LoadAnalyzer tool
- Write a scientific paper on the experiments and results

## Hardware and Software

- **Robot**: Husky A200
- **Scanner**: [RoadLoad](https://github.com/umoe1001/RoadLoadAnalyzer/tree/main/RoadLoad) system
- **Software**: umx_driver um6, LoadAnalyzer
- **Data Processing**: Python, Pandas, NumPy, PyLife

## Experiments

1. **Identify and Construct Rough Roads**:
   - Three different rough roads were selected and constructed.
   - These roads serve as the test track for the Husky A200.

2. **Reference Scans**:
   - The rough roads were scanned using the [RoadLoad](https://github.com/umoe1001/RoadLoadAnalyzer/tree/main/RoadLoad) system to obtain a reference for analysis.

3. **Driving Tests with the Husky A200**:
   - The umx_driver um6 was applied to the Husky A200.
   - The Husky A200 was driven over the rough roads to collect real load data.

## Data Analysis

- **Rainflow Counting Method**: The rainflow counting method was used to identify and classify load cycles in the collected data.
- **Damage Accumulation**: Based on rainflow counting, the damage for each identified cycle was calculated.
- **Pseudo-Damage**: The total pseudo-damage was determined by summing the individual damages for all load cycles.

## Results

- The analysis showed that the Husky A200 exhibited different damage potentials under various loads.
- The pseudo-damage and equivalent load were calculated for the different rough roads.
- The results of the analysis were documented in a scientific paper.

## Conclusion

This project successfully demonstrated the application of real experiments for load data analysis with the Husky A200. The collected data and results provide valuable insights into the fatigue properties of the robot under different conditions.

## References

- [PyLife Documentation](https://github.com/bos)
