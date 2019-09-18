/*
 * Expression.h
 *
 *  Created on: 16 сент. 2019 г.
 *      Author: sadko
 */

#ifndef CORE_CALC_EXPRESSION_H_
#define CORE_CALC_EXPRESSION_H_

#include <core/status.h>
#include <core/LSPString.h>
#include <core/io/IInSequence.h>
#include <core/calc/types.h>
#include <core/calc/Resolver.h>

#include <data/cstorage.h>
#include <data/cvector.h>

namespace lsp
{
    namespace calc
    {
        struct expr_t;
        
        class Expression
        {
            private:
                Expression & operator = (const Expression &);

            public:
                enum expr_flags
                {
                    FLAG_MULTIPLE       = 1 << 0
                };

            protected:
                typedef struct root_t
                {
                    expr_t         *expr;
                    value_t         result;
                } root_t;

                typedef struct param_t
                {
                    LSPString       name;
                    value_t         value;
                } param_t;

            protected:
                Resolver           *pResolver;
                cstorage<root_t>    vRoots;

            protected:
                status_t            evaluate(value_t *result, expr_t *expr);
                void                destroy_all_data();

            public:
                explicit Expression(Resolver *res);
                virtual ~Expression();

                void destroy();

            public:
                /**
                 * Parse the expression
                 * @param expr string containing expression
                 * @param charset character set, may be NULL for default character set
                 * @param flags additional flags
                 * @return status of operation
                 */
                status_t    parse(const char *expr, const char *charset = NULL, size_t flags = 0);

                /**
                 * Parse the expression
                 * @param expr string containing expression
                 * @param flags additional flags
                 * @return status of operation
                 */
                status_t    parse(const LSPString *expr, size_t flags = 0);

                /**
                 * Parse the expression
                 * @param seq character input sequence
                 * @param flags additional flags
                 * @return status of operation
                 */
                status_t    parse(io::IInSequence *seq, size_t flags = 0);

                /**
                 * Check that expression is valid
                 * @return true if the expression is valid
                 */
                inline bool     valid() const { return vRoots.size() > 0; };

                /**
                 * Evaluate all the expressions
                 * @param result pointer to return value of the zero-indexed expression
                 * @return status of operation
                 */
                status_t        evaluate(value_t *result = NULL);

                /**
                 * Evaluate the specific expression
                 * @param index expression index
                 * @param result pointer to return value of the specified expression
                 * @return status of operation
                 */
                status_t        evaluate(size_t idx, value_t *result = NULL);

                /**
                 * Get number of results
                 * @return number of results
                 */
                inline size_t   results() const { return vRoots.size() > 0; };

                /**
                 * Get result of the specific expression
                 * @param result the pointer to store the result
                 * @param idx the result indes
                 * @return status of operation
                 */
                status_t        result(value_t *result, size_t idx);
        };
    
    } /* namespace calc */
} /* namespace lsp */

#endif /* CORE_CALC_EXPRESSION_H_ */
