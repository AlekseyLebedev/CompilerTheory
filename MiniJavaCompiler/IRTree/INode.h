#pragma once
namespace IRTree {
	class IRTreeVisitor;
	
	class INode {
	public:
		virtual void Accept( IRTreeVisitor* visitor ) const = 0;
	};
}