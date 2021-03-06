/*!
 * \file evolutions.hpp
 * \author Cyrielle
 * \copyright GNU GPL v3.0
 * \warning This file is to be completely redone later. It way not have a lot of documentation.
 */
#ifndef EVOLUTIONS_HPP_INCLUDED
#define EVOLUTIONS_HPP_INCLUDED

#include "Evolution.hpp"
#include "Item.hpp"
#pragma GCC diagnostic ignored "-Wunused-parameter"
namespace OpMon {

    /**
     * \brief Namespace containing evolution definitions
     */
    namespace Evolutions {

        class E_Item : public Evolution {
          public:
            E_Item(int evo, std::string const &itemID);
            bool checkEvolve(OpMon const &toCheck) const;

          protected:
            const std::string itemID;
        };

        class E_Level : public Evolution {
          public:
            E_Level(int evo, int level);
            bool checkEvolve(OpMon const &toCheck) const;

          private:
            int level;
        };
    } // namespace Evolutions

    using namespace Evolutions;
} // namespace OpMon
#pragma GCC diagnostic pop
#endif // EVOLUTIONS_HPP_INCLUDED
