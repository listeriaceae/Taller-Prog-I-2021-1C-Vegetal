#include <array>
#include "Barril.hpp"

static constexpr std::array<std::pair<punto32_t, punto32_t>, 12> direcciones{
  std::make_pair(punto32_t{ to_fixed32(128), to_fixed32(84 - ALTO_BARRIL) },
                 punto32_t{ to_fixed32(1), to_fixed32(0.0625) }),
  std::make_pair(punto32_t{ to_fixed32(208), to_fixed32(89 - ALTO_BARRIL) },
                 punto32_t{ 0, to_fixed32(1) }),
  std::make_pair(punto32_t{ to_fixed32(208), to_fixed32(110 - ALTO_BARRIL) },
                 punto32_t{ to_fixed32(-1), to_fixed32(0.0625) }),
  std::make_pair(punto32_t{ to_fixed32(16 - ANCHO_BARRIL),
                            to_fixed32(122.75 - ALTO_BARRIL) },
                 punto32_t{ 0, to_fixed32(1) }),
  std::make_pair(punto32_t{ to_fixed32(16 - ANCHO_BARRIL),
                            to_fixed32(142.75 - ALTO_BARRIL) },
                 punto32_t{ to_fixed32(1), to_fixed32(0.0625) }),
  std::make_pair(punto32_t{ to_fixed32(208), to_fixed32(155.5 - ALTO_BARRIL) },
                 punto32_t{ 0, to_fixed32(1) }),
  std::make_pair(punto32_t{ to_fixed32(208), to_fixed32(175.5 - ALTO_BARRIL) },
                 punto32_t{ to_fixed32(-1), to_fixed32(0.0625) }),
  std::make_pair(punto32_t{ to_fixed32(16 - ANCHO_BARRIL),
                            to_fixed32(188.25 - ALTO_BARRIL) },
                 punto32_t{ 0, to_fixed32(1) }),
  std::make_pair(punto32_t{ to_fixed32(16 - ANCHO_BARRIL),
                            to_fixed32(208.25 - ALTO_BARRIL) },
                 punto32_t{ to_fixed32(1), to_fixed32(0.0625) }),
  std::make_pair(punto32_t{ to_fixed32(208), to_fixed32(221 - ALTO_BARRIL) },
                 punto32_t{ 0, to_fixed32(1) }),
  std::make_pair(punto32_t{ to_fixed32(208), to_fixed32(241 - ALTO_BARRIL) },
                 punto32_t{ to_fixed32(1), 0 }),
  {}
};

void
Barril::mover()
{
  pos.x += vel.x;
  pos.y += vel.y;
  if (pos == direcciones[direcciones_index].first) {
    vel = direcciones[direcciones_index++].second;
  }
}
