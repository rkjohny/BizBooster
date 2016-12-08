
#ifndef COMMON_TRAITS_H
#define COMMON_TRAITS_H


#define NON_COPY_ABLE(TYPE) \
        TYPE(TYPE&) = delete; \
        TYPE(TYPE&&) = delete; \

#define NON_ASSIGN_ABLE(TYPE) \
        TYPE& operator=(TYPE&) = delete; \
        TYPE& operator=(TYPE&&) = delete;

#define NON_COPY_NON_ASSIGN_ABLE(TYPE) \
        TYPE(TYPE&) = delete; \
        TYPE& operator=(TYPE&) = delete; \
        TYPE(TYPE&&) = delete; \
        TYPE& operator=(TYPE&&) = delete;

#endif //COMMON_TRAITS_H
