[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6524567&assignment_repo_type=AssignmentRepo)
# Project 2: Extending the Ray Tracer
# CS 440 Computer Graphics, Fall 2021
***

# Purpose

This project extends the ray tracer developed in Homework 3. It implements some of the ray tracing topics we have covered, namely:

- ray casting
- shading
- anti-aliasing
- light sources
- acceleration structures

# Background

For this homework, you must

- have a working solution to Homework 3
- know how to read and write object oriented code in C++
- understand the concepts listed above
- know how to compile a C++ project spanning multiple files in multiple directories
- know vector arithmetic

# The Problem Set

The problems are defined in `proj2.tex` which is to be compiled using a LaTeX compiler.

# Time Requirement

Based on feedback from the last set of students that attempted this assignment, the number of hours that your team will require to complete this homework are as follows.

- (min, max) : (37, 160)
- (mean, median, st.dev.) : (83.6, 50, 47.1)

# Last year's feedback

A summary of the feedback on this project from last year is included in `old-feedback.md`. It did not have the "Improvement" question. Similar comments have been merged and condensed and some comments specific to the offering have been redacted. Based on the feedback, a longer time period is assigned with ample time after final exams.

# Submission

There are 2 parts to the submission.

## 1 Problem Set

Submit _all_ code files in the `raytracer` folder. `World.cpp` should `#include` the relevant file from the `build` folder corresponding to the high-res version of your showcase scene. Other `World::build` implementations (e.g. for the low-res version, or used to generate other pictures on your web page) should be included in the `build` folder. Compiling and running `raytracer.cpp` in the `raytracer` folder should generate the high-res image.

Include a `website` folder that includes your website, either as HTML, markdown, or a URL. The submitted web page must be complete, i.e. all the required assets are submitted and no links are broken.

This is a team submission on GitHub and contributes to your _Submission Score_.

_Deadline_: 2359h on Sunday, 19 December

## 2 Feedback Form

You will provide feedback on your buddies and on the project. The feedback form will be available on LMS with further instructions and will be due at the same time as the problem set.

This is an individual submission on LMS and contributes to your individual _Team Factor_ which is 1 by default and penalized for non-submission of the feedback or non-participation in the team as assessed through peer feedback or GitHub contribution.

_Deadline_: 2359h on Sunday, 19 December

# Grading

Your submission will be graded as per the criteria specified in the accompanying file, _rubric.xlsx_. This will contribute to your _Submission Score_.

Your individual score in this homework is the product of your Submission Score and Team Factor.

# Resources

Please find useful resources for the project on the [Project 2 Resources](https://hulms.instructure.com/courses/1622/pages/project-2-resources?module_item_id=55192) page on LMS.

# Fun Stuff

The engine can be extended _ad infinitum_. Below are some recommendations but these need not limit you.

- adding interesting materials
- adding texturing
- adding optical effects
- adding a variety of acceleration structures
- implementing parallelization
- adding bump or normal mapping
- adding sophisticated ray tracers

## Discussion

There is a lot to handle and there are bound to be confusions and queries. Please utilize the following avenues.

There is a lot to handle and there are bound to be confusions and queries. Please share them using the following avenues.

- discuss with your buddies,
- the corresponding discussion thread on LMS,
- discuss with your peers,
- consult with course staff.

# Tips

- Do not include identifying information in your submission.
- Only include images which you are comfortable sharing publicly.
- There is no late submission. Submit whatever you have by the deadline.
- viel Spaß!

# Compilation Instruction (for self-reference)

1. Goto ray tracer directory from root with : 
    cd raytracer
2. Compile with:
    g++ -o test.exe -I ./utilities/*.cpp test.cpp
3. Run with:
    .\test.exe


1. Goto ray tracer directory from root with : 
    cd raytracer
2. Compile with:
    g++ main.cpp build/buildChapter14.cpp acceleration/*.cpp cameras/*.cpp geometry/*.cpp materials/*.cpp samplers/*.cpp tracers/*.cpp utilities/*.cpp world/*.cpp BRDF/*.cpp lights/*.cpp -O -Wall -o main.exe -g

    g++ main.cpp build/buildTest.cpp acceleration/*.cpp cameras/*.cpp geometry/*.cpp materials/*.cpp samplers/*.cpp tracers/*.cpp utilities/*.cpp world/*.cpp BRDF/*.cpp lights/*.cpp -O -Wall -o main.exe -g

    
3. Run with:
    .\main.exe