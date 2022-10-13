# **OperatingSystem-7064**
## **Assignment 2 - CPU scheduler in C++**

### _**Our targets:**_
1.  Program produces a valid output scheduling within 5 minutes (0.3 marks)
2.  Scheduling is different from baseline (0.3 marks)
3.  Scheduling has a smaller total wait time as compared to the baseline (0.3 marks)
4.  Scheduling has a smaller longest response time as compared to the baseline
5.  Scheduling contains fewer switches between customers as compared to the baseline (0.6 marks)
6.  Scheduling has a smaller total wait time for high priority customers as compared to the total wait time for regular customers (0.6 marks)

### _**Suggestion:**_

#### **Target 3 - less total wait time:**
> [total wait time = sum of wait times for all customers in the given input file]

`Solutioin: Use shortest-job-first approach`



#### **Target 4 - less response time**
> [longest response time = maximum response time across customers in the given input]
> [response time for a customer = index of the time slot where the customers plays for the first time minus index of time slot where the customer arrived]

`Solutioin: New arrvied processes have higher priority for first run`


#### **Target 5 - less context switches:**
> [number of switches = number of time slots (starting from 1), such that the occupation in the previous time slot doesn't match the occupation in this time slot]

`Solutioin 1: When preempt haapying, check if the process can complete within next time slot then don't preempt it`

`Solutioin 2: Dynamic adjust the preempt solt time by no. of process waiting`


#### **Target 6 - members wait less than non-members:**
> [wait time for a customer = time before 1st run + time in waiting list]

`Solutioin: Use two queues for members and non-members (can keep use one stack, and pop members before non-members)`


### Run and Test code:
#### [Windows base]  
<img src="https://github.com/andy30sh/OperatingSystem-7064/blob/main/picture/1.png" alt="Complie code" style="width:600px;"/>
<img src="https://github.com/andy30sh/OperatingSystem-7064/blob/main/picture/2.png" alt="Complie code" style="width:600px;"/>
<img src="https://github.com/andy30sh/OperatingSystem-7064/blob/main/picture/3.png" alt="Complie code" style="width:600px;"/>

