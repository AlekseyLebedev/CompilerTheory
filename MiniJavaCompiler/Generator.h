#pragma once
#include <memory>
#include <map>
#include <list>
#include "IRTree\StatementClasses\IRTSSeq.h"

using namespace IRTree;

class CGenerator {

private:
	// ������ ������ ���� ������ � ���� ���������� �� ������������ �������
	std::list<std::shared_ptr<IRTSSeq> > basicBlocks;
};