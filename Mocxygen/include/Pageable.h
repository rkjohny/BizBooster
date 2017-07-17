/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef PAGEABLE_H
#define PAGEABLE_H

#include "Json.h"


#define DEFAULT_ITEM_PER_PAGE 20;

namespace Mocxygen {

    class Pageable {
    public:
        Pageable() {
            m_itemPerPage = DEFAULT_ITEM_PER_PAGE;
        }

        virtual ~Pageable() = default;

        int GetPageNumver() const;
        void SetpageNumber(int pageNumber);

        int GetItemPerPage() const;
        void SetItemPerPage(int itemperPage);


        REGISTER_GETTER_START
        GETTER(Pageable, int, "pageNumber", &Pageable::GetPageNumver),
        GETTER(Pageable, int, "itemPerPage", &Pageable::GetItemPerPage)
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        SETTER(Pageable, int, "pageNumber", &Pageable::SetpageNumber),
        SETTER(Pageable, int, "itemPerPage", &Pageable::SetItemPerPage)
        REGISTER_GETTER_END

    private:
        int m_pageNumber;
        int m_itemPerPage;
    };
}
#endif //PAGEABLE_H
