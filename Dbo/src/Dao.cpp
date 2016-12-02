#include"Dao.h"
#include "DboConstant.h"
#include "PGSqlDaoImp.h"

namespace Dbo {

Dao::Dao()
{}

Dao::Dao(Dao &d)
{}

Dao::~Dao()
{}

Dao *Dao::GetInstance()
{
#ifdef PGSQL
    return PGSqlDaoImp::GetInstance();
#else
    return nullptr;
#endif
}

}