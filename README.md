# Naval Traffic Estimate in Venice

Project - Image Processing and Transmission (140127) - Federico Favia & Martin De Pellegrini, May 2018, University of Trento, Trento

This Computer Vision project developed within the course of Image Processing and Transmission at University of Trento investigates some ways to evaluate the naval traffic in Venice from a webcam video of the Grand Canal (cut in several moments from a  [live stream](https://www.youtube.com/watch?v=BPXtn15_9qo) in YouTube).  . 

In particular motion detection algorithms are used (adaptive background subtraction), and then morphological filters and blob detection are implemented to count the number of boats and estimating the traffic. 
Several metrics are evaluated for the results such as integral average, median and flow rate. See the report (unfortunately in Italian Language only until now) for more information.
The project is written in C++ and OpenCV library. The main file is "venice_etiproject_2018.cpp". Also a Matlab script is provided to run more experiments and evaluate the mathematical results in term of plots and considerations.

See below some snapshots from the results of the project:
![Script](https://github.com/favia96/navaltraffic_estimate_venice/blob/master/report%26demo/script.png)
![Plot](https://github.com/favia96/navaltraffic_estimate_venice/blob/master/report%26demo/plot.png)

