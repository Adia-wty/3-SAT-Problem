# 3-SAT Problem
Project on understanding the computational pattern of 3-SAT Problem

## Introduction
Determining whether a set of clauses is satisfiable or not is a fundamental problem in **knowledge representation and reasoning** (and in Artificial Intelligence and Computer Science where it was the problem considered in describing the notion of NP-complete problems).
In order to understand better the computational nature of the satisfiability problem, researchers have investigated various instances of the problem. And one well studied instance is **3-SAT**.

## 3-SAT
3-SAT problem stands for *3-Satisfiability Problem*.
### Input: 
A collection of clauses <a href="https://www.codecogs.com/eqnedit.php?latex=$C_i$" target="_blank"><img src="https://latex.codecogs.com/png.latex?$C_i$" title="$C_i$" /></a>
### Output: 
Whether the defined problem is satisfiable, in other words, is there a truth assignment to every variable in domain V such that each clause is satisfied.
#### Definition : clause is a disjunction of literals. 
In 3-SAT, the clause has exactly 3 literals and is in the form of <a href="https://www.codecogs.com/eqnedit.php?latex=$x_1&space;\vee&space;x_2&space;\vee&space;x_3$" target="_blank"><img src="https://latex.codecogs.com/png.latex?$x_1&space;\vee&space;x_2&space;\vee&space;x_3$" title="$x_1 \vee x_2 \vee x_3$" /></a>, where  <a href="https://www.codecogs.com/eqnedit.php?latex=$x_1,&space;x_2,&space;x_3\in&space;V$" target="_blank"><img src="https://latex.codecogs.com/png.latex?$x_1,&space;x_2,&space;x_3\in&space;V$" title="$x_1, x_2, x_3\in V$" /></a>.
Thus, we need at least one literal to be true to make the whole clause to be true. 

### Importance of 3-SAT problem
It can be shown that it is always possible to translate every instance of satisfiability into an instance of 3-SAT without changing the result of whether it is satisfiable. So it will be easier for us to step into other satisfiability problems if we can figure out the nature of 3-SAT problem first.

## Goal
The goal of this project is to determine empirically at what point the satisfiability problem becomes difficult, in other words, at what ratio of clauses to variables the satisfiability problem becomes hard.

## Tool
I use a satisfiability solver [**MiniSAT**](www.minisat.se) to get the result of each case.
To use the MiniSAT, we will need a file in which the collection of clauses is described in a certain language. Below is an example of such file.

```txt
p cnf 5 4
1 -5 4 0
-1 2 3 0
-3 -4 2 0
-1 -2 3 0
```

The first line is the header. 
**p cnf** indicates this file is in cnf (conjunctive normal form) format.
The first number after it defines the maximum number of variables that can appear in this problem.
The second number defines the total number of clauses.
Each line starting from the second line is a clause, each clause is terminated by **0**.
The first three non-zero number denotes three different literals, with negative numbers being negative literals of that variable. 

So basically the above file means that at most 5 variables will appear in this file and there are 4 clauses in total. If the variables are a, b, c, d, e, then their corresponding number is 1, 2, 3, 4, 5. The first clause is <a href="https://www.codecogs.com/eqnedit.php?latex=a&space;\vee&space;\neg&space;e&space;\vee&space;d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a&space;\vee&space;\neg&space;e&space;\vee&space;d" title="a \vee \neg e \vee d" /></a>. The second clause is <a href="https://www.codecogs.com/eqnedit.php?latex=\neg&space;a&space;\vee&space;b&space;\vee&space;c" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\neg&space;a&space;\vee&space;b&space;\vee&space;c" title="\neg a \vee b \vee c" /></a>.

Then we can type ```minisat file.cnf``` in terminal to get the result (whether it is satisfiable, time usage to solve this problem, how many propagations during the process...)

So next question comes that how to indicate hardness of each problem?

In this project, I decide to use propagation to indicate hardness since the runtime may depend on the configuration of computer.

With all the preparation, now we can start to solve the problem.

## Steps
### 1. Generate files with different ratios
First, we generate files of different ratios in C. More specifically, we need to fill the number of propagation in the following table.
![image](https://github.com/Adia-wty/3-SAT-Problem/blob/master/Reslult/Empty_Table.png)

So the blank in the left upper corner means that in a 3-SAT problem which contains at most 50 variables and 50 clauses since the ratio is 1, how many propagation is needed. In these files, the clauses are generated randomly. So for each blank, 10 instances are needed to calculate the average of propagations to make the result more reliable. 

### 2. Process the files with MiniSAT
It requires another C program since we need to type in terminal to call MiniSAT and we have 1000 files to process.

### 3. Collect data
Since the result is shown in the terminal, we write another program to send all the data from terminal to C. The filled table is shown below.

![image](https://github.com/Adia-wty/3-SAT-Problem/blob/master/Reslult/Data_Table.png)

### 4. Plot the graph
At last, with the data we get, a graph can be plotted, which shows that 3-SAT has an easy-hard-easy computational pattern. 
For small ratio and large ratio, the satisfiability problem can be solved easily. The hardness increases fairly sharply around ratio = 4.25.

![image](https://github.com/Adia-wty/3-SAT-Problem/blob/master/Reslult/Propagation_vs_Ratio.png)

## Analysis
When we try to understand the result, we find that it is in expectation. 

Basically, when the ratio is small, which means that there are far more variables than clauses, it is easy to make the problem satisfiable because there are fewer constraints in assigning truth values to the variables. 

When the ratio is large, which means that there are far more clauses than variables, it is also easy because there are too many constraints to assign truth values to the variables and the set is usually unsatisfiable. 

Somewhere in between these two extremes the satisfiability problem becomes hard. 

![image](https://github.com/Adia-wty/3-SAT-Problem/blob/master/Reslult/Analysis.png) 

## Comparison
The following result is from a [similar research of Stanford University](http://robotics.stanford.edu/~shoham/www%20papers/CP04randomsat.pdf), in which the result is 4.26, which is quite close to my conclusion. 
![image](https://github.com/Adia-wty/3-SAT-Problem/blob/master/Reslult/Result_of_Similar_Research.png)

## Result
Finally this project shows that 
* **3-SAT exhibits an easy-hard-easy computational pattern**
* **Around the ratio of 4.25 the 3-SAT becomes hardest to solve**. I completed this project in 2019 Jan under the guidance of Martin Aleksandrov in Technische Universität Berlin. He is really an excellent professor and gave me much insight in Artificial Intelligence.

## Acknowledgement
I completed this project in January 2019 under the guidance of Professor Martin Aleksandrov in Technische Universität Berlin. He is really excellent and gave me much more insight in Artificial Intelligence than I expected.
