#ifndef QUICK_ULTRA_SCANNER_MACROS_HPP
#define QUICK_ULTRA_SCANNER_MACROS_HPP

#include <vector>

namespace quick {
namespace ultra {

#define ENTITY struct
#define IMPORT class

#define ID

template<typename T>
using OneToOne = T*;

template<typename T>
using OneToMany = std::vector<T*>;

template<typename T>
using ManyToMany = std::vector<T*>;

template<typename T>
using ManyToOne = T*;

#define ONE_TO_ONE(T)   ::quick::ultra::OneToOne<T>
#define ONE_TO_MANY(T)  ::quick::ultra::OneToMany<T>
#define MANY_TO_MANY(T) ::quick::ultra::ManyToMany<T>
#define MANY_TO_ONE(T)  ::quick::ultra::ManyToOne<T>

} 
} 

#endif