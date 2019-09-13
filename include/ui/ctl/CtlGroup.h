/*
 * CtlGroup.h
 *
 *  Created on: 17 июл. 2017 г.
 *      Author: sadko
 */

#ifndef UI_CTL_CTLGROUP_H_
#define UI_CTL_CTLGROUP_H_

namespace lsp
{
    namespace ctl
    {
        class CtlGroup: public CtlWidget
        {
            public:
                static const ctl_class_t metadata;

            protected:
                CtlColor        sColor;
                CtlColor        sTextColor;

            public:
                explicit CtlGroup(CtlRegistry *src, LSPGroup *widget);
                virtual ~CtlGroup();

            public:
                virtual void init();

                virtual void set(widget_attribute_t att, const char *value);

                virtual status_t add(CtlWidget *child);
        };
    
    } /* namespace ctl */
} /* namespace lsp */

#endif /* UI_CTL_CTLGROUP_H_ */
