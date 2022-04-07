#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>

class MasodikOpenMP
{
private:
	void DummyCalcA();
	void DummyCalcB();
public:
	MasodikOpenMP();
	void SectionsTest();
	void ScopeTest();
	void ScheduleTest();
};

