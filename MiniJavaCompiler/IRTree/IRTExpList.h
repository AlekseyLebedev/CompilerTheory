#pragma once

#include <memory>
#include "IRTExpression.h"

namespace IRTree {

    class IRTExpList : public IRTExpression
    {
    public:
		IRTExpList( const std::shared_ptr<IRTExpression> _head, const std::shared_ptr<IRTExpList> _tail );

		const std::shared_ptr<IRTExpression> GetHead() const;
		const std::shared_ptr<IRTExpList> GetTail() const;
		std::shared_ptr<IRTExpression> GetHead();
		std::shared_ptr<IRTExpList> GetTail();

        void Accept( IVisitor* visitor ) const;

    private:

        const std::shared_ptr<IRTExpression> head;
        const std::shared_ptr<IRTExpList> tail;

    };
}
