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

#include "Pageable.h"

namespace Mocxygen {

    int Pageable::GetPageNumver() const {
        return m_pageNumber;
    }

    void Pageable::SetpageNumber(int pageNumber) {
        m_pageNumber = pageNumber;
    }

    int Pageable::GetItemPerPage() const {
        return m_itemPerPage;
    }

    void Pageable::SetItemPerPage(int itemperPage) {
        m_itemPerPage = itemperPage;
    }
}