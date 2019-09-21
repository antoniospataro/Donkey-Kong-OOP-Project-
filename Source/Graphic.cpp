#include "../Headers/Graphic.h"

int x = 0;
int y = 0;
int pixel = 16;
Graphic::Graphic(int scaleW, int scaleH, int scaleX, int scaleY,
                 ALLEGRO_BITMAP *buffer, ALLEGRO_DISPLAY *display) {
  this->level = 1;
  fstream input;
  input.open("../Maps/Map1.map");
  if (input.is_open())
    input >> ::x >> ::y;
  if (input.is_open())
    for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
        input >> matrix[i][j];
  input.close();
  win = false;
  death = false;
  bonus = false;
  font = al_load_ttf_font("../Font/DejaVuSans.ttf", 20, 0);
  this->scale_h = scaleH;
  this->scale_w = scaleW;
  this->scale_x = scaleX;
  this->scale_y = scaleY;
  this->buffer = buffer;
  this->display = display;
}
void Graphic::drawMenu(bool start) {
  al_set_target_bitmap(buffer);
  bmp = al_load_bitmap("../Sprites/dk.png");
  al_draw_bitmap(bmp, (pixel * x) / 2, (pixel * y) / 500, 0);
  al_destroy_bitmap(bmp);
  if (start) {
    bmp = al_load_bitmap("../Sprites/Start1.png");
    al_draw_bitmap(bmp, (pixel * x) / 2, (pixel * y) / 3, 0);
    al_destroy_bitmap(bmp);
    bmp = al_load_bitmap("../Sprites/Exit2.png");
    al_draw_bitmap(bmp, (pixel * x) / 2, (pixel * y) / 2, 0);
    al_destroy_bitmap(bmp);
  }
  if (!start) {
    bmp = al_load_bitmap("../Sprites/Start2.png");
    al_draw_bitmap(bmp, (pixel * x) / 2, (pixel * y) / 3, 0);
    al_destroy_bitmap(bmp);
    bmp = al_load_bitmap("../Sprites/Exit1.png");
    al_draw_bitmap(bmp, (pixel * x) / 2, (pixel * y) / 2, 0);
    al_destroy_bitmap(bmp);
  }
  al_set_target_backbuffer(this->display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, (y * pixel), (x * pixel), scale_x,
                        scale_y, scale_w, scale_h, 0);
}
void Graphic::setDk(DonkeyKong &dk) {
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      if (matrix[i][j] == 3 && matrix[i][j + 1] == 3) {
        dk.setX((j + 2) * pixel);
        dk.setY((i - 1) * pixel);
        i = x;
        j = y;
      }
}
void Graphic::setMario(Mario &m) {
  m.setFall(false);
  m.setJump(false);
  m.setSpace(false);
  m.setJmp(0);
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      if (matrix[i][j] == 3) {
        if (j != j - 1) {
          if (matrix[i][j + 1] == 0) {
            m.setX((j + 1) * pixel);
            m.setY((i)*pixel);
          }
        } else {
          if (matrix[i][j - 1] == 0) {
            m.setX((j - 1) * pixel);
            m.setY((i)*pixel);
          }
        }
      }
}
void Graphic::drawMap() {
  al_set_target_bitmap(buffer);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++) {
      switch (matrix[i][j]) {
      case 1:
        if (level == 5)
          bmp = al_load_bitmap("../Sprites/Floor2.png");
        else
          bmp = al_load_bitmap("../Sprites/Floor.png");
        al_draw_bitmap(bmp, j * pixel, i * pixel, 0);
        al_destroy_bitmap(bmp);
        break;
      case 2:
        if (level == 5)
          bmp = al_load_bitmap("../Sprites/Scale2.png");
        else
          bmp = al_load_bitmap("../Sprites/Scale.png");
        al_draw_bitmap(bmp, j * pixel, i * pixel, 0);
        al_destroy_bitmap(bmp);
        break;
      case 3:
        bmp = al_load_bitmap("../Sprites/Barrel0.png");
        al_draw_bitmap(bmp, j * pixel, i * pixel, 0);
        al_destroy_bitmap(bmp);
        break;
      case 4:
        bmp = al_load_bitmap("../Sprites/Hammer.png");
        al_draw_bitmap(bmp, j * pixel, i * pixel, 0);
        al_destroy_bitmap(bmp);
        break;

      case 5:
        fires.push_back(Fire(j * pixel, i * pixel));
        matrix[i][j] = 0;
        break;
      default:
        break;
      }
    }
  al_set_target_backbuffer(this->display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, (y * pixel), (x * pixel), scale_x,
                        scale_y, scale_w, scale_h, 0);
}
void Graphic::drawFires(Mario &m, DonkeyKong &dk) {
  if (fires.empty()) {
    return;
  }
  al_set_target_bitmap(buffer);
  for (int i = 0; i < fires.size(); i++) {
    if (fires[i].getX() == 0) {
      fires[i].setLeft(false);
      fires[i].setRight(true);
    } else if (fires[i].getX() / 16 == (y - 1)) {
      fires[i].setLeft(true);
      fires[i].setRight(false);
    }
    fires[i].Draw();
    if ((fires[i].getX() == m.getX() && fires[i].getY() == m.getY()) ||
        (fires[i].getX() + 8 == m.getX() && fires[i].getY() == m.getY()) ||
        (fires[i].getX() - 8 == m.getX() && fires[i].getY() == m.getY()) ||
        (fires[i].getX() == m.getX() && fires[i].getY() - 8 == m.getY()) ||
        (fires[i].getX() + 8 == m.getX() && fires[i].getY() - 8 == m.getY()) ||
        (fires[i].getX() - 8 == m.getX() && fires[i].getY() - 8 == m.getY())) {
      m.setLife(m.getLife() - 1);
      if (m.getLife() == 0) {
        level = 0;
        m.setLife(10);
        setMap(m, dk);
      } else
        setThisMap(m);
      fires.clear();
      death = true;
    }

    al_set_target_backbuffer(this->display);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(buffer, 0, 0, (y * pixel), (x * pixel), scale_x,
                          scale_y, scale_w, scale_h, 0);
  }
}
void Graphic::drawDK(DonkeyKong &dk) {
  al_set_target_bitmap(buffer);
  dk.Draw();
  if (dk.getCont() == 22) {
    barrels.push_back(Barrel(dk.getX() + 48, dk.getY() + 32));
  }
  al_set_target_backbuffer(this->display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, (y * pixel), (x * pixel), scale_x,
                        scale_y, scale_w, scale_h, 0);
}
void Graphic::drawBarrels(Mario &m, DonkeyKong &dk) {
  if (barrels.empty())
    return;
  al_set_target_bitmap(buffer);
  for (int i = 0; i < barrels.size(); i++) {
    if (barrels[i].getX() == 0) {
      barrels[i].setLeft(false);
      barrels[i].setRight(true);
    } else if (barrels[i].getX() / 16 == (y - 1)) {
      barrels[i].setLeft(true);
      barrels[i].setRight(false);
    }
    if (barrels[i].getDown() && barrels[i].getY() % 16 == 0 &&
        matrix[barrels[i].getY() / 16 + 1][barrels[i].getX() / 16] == 1)
      barrels[i].setDown(false);
    if (!barrels[i].getDown() && barrels[i].getX() % 16 == 0 &&
        matrix[barrels[i].getY() / 16 + 2][barrels[i].getX() / 16] == 2)
      barrels[i].setDown(rand() % 2);
    barrels[i].Draw();
    if (barrels[i].getX() % 16 == 0 &&
        matrix[barrels[i].getY() / 16 + 1][barrels[i].getX() / 16] == 0)
      barrels[i].setFall(true);
    if (barrels[i].getY() % 16 == 0 &&
        matrix[barrels[i].getY() / 16 + 1][barrels[i].getX() / 16] == 1)
      barrels[i].setFall(false);
    if ((barrels[i].getX() == m.getX() || barrels[i].getX() == m.getX() + 8 ||
         barrels[i].getX() == m.getX() - 8) &&
        (barrels[i].getY() == m.getY() + 8 ||
         barrels[i].getY() == m.getY() - 8 || barrels[i].getY() == m.getY()) &&
        !m.getHammer()) {
      m.setLife(m.getLife() - 1);
      if (m.getLife() == 0) {
        level = 0;
        m.setLife(10);
        setMap(m, dk);
      } else
        setThisMap(m);
      barrels.clear();
      death = true;
    } else if (barrels[i].getX() == m.getX() + 16 &&
               barrels[i].getY() == m.getY() && m.getHammer() &&
               !m.getReverse()) {
      m.setLife(m.getLife() - 1);
      if (m.getLife() == 0) {
        level = 0;
        m.setLife(10);
        setMap(m, dk);
      } else
        setThisMap(m);
      death = true;
      barrels.clear();
      m.setHammer(false);
      m.setJump(false);
    } else if (barrels[i].getX() == m.getX() - 16 &&
               barrels[i].getY() == m.getY() && m.getHammer() &&
               m.getReverse()) {
      m.setLife(m.getLife() - 1);
      if (m.getLife() == 0) {
        level = 0;
        m.setLife(10);
        setMap(m, dk);
      } else
        setThisMap(m);
      death = true;
      barrels.clear();
      m.setHammer(false);
      m.setJump(false);
    } else if ((barrels[i].getY() == m.getY()) &&
               (barrels[i].getX() == m.getX() ||
                (barrels[i].getX() <= m.getX() + 16 &&
                 barrels[i].getX() >= m.getX() - 16)) &&
               m.getHammer() && !m.getReverse()) {
      Barrel temp(0, 0);
      temp = barrels[i];
      barrels[i] = barrels[barrels.size() - 1];
      barrels[barrels.size() - 1] = temp;
      barrels.pop_back();
    } else if ((barrels[i].getY() == m.getY()) &&
               (barrels[i].getX() == m.getX() ||
                (barrels[i].getX() <= m.getX() + 16 &&
                 barrels[i].getX() >= m.getX() - 16)) &&
               m.getHammer() && m.getReverse()) {
      Barrel temp(0, 0);
      temp = barrels[i];
      barrels[i] = barrels[barrels.size() - 1];
      barrels[barrels.size() - 1] = temp;
      barrels.pop_back();
    } else if (matrix[barrels[i].getY() / 16][barrels[i].getX() / 16] == 3) {
      Barrel temp(0, 0);
      temp = barrels[i];
      barrels[i] = barrels[barrels.size() - 1];
      barrels[barrels.size() - 1] = temp;
      barrels.pop_back();
    }
  }
  al_set_target_backbuffer(this->display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, (y * pixel), (x * pixel), scale_x,
                        scale_y, scale_w, scale_h, 0);
}
void Graphic::drawMario(Mario &m, DonkeyKong &dk) {
  al_set_target_bitmap(buffer);
  if (matrix[m.getY() / 16][m.getX() / 16] == 2 &&
      matrix[m.getY() / 16 + 1][m.getX() / 16] == 2 && !m.getScale())
    m.setFall(true);
  if (matrix[m.getY() / 16][m.getX() / 16] == 4 ||
      (matrix[m.getY() / 16][m.getX() / 16 - 1] == 4 && m.getX() % 16 != 0) ||
      (matrix[m.getY() / 16][m.getX() / 16 + 1] == 4 && m.getX() % 16 != 0)) {
    m.setHammer(true);
    m.setFall(true);
    if (matrix[m.getY() / 16][m.getX() / 16] == 4)
      matrix[m.getY() / 16][m.getX() / 16] = 0;
    else if (matrix[m.getY() / 16][m.getX() / 16 + 1] == 4)
      matrix[m.getY() / 16][m.getX() / 16 + 1] = 0;
    else if (matrix[m.getY() / 16][m.getX() / 16 - 1] == 4)
      matrix[m.getY() / 16][m.getX() / 16 - 1] = 0;
  }
  if (m.getHammer()) {
    m.setcontatoreHammer(m.getcontatoreHammer() + 1);
  } else {
    m.setcontatoreHammer(0);
  }
  if (m.getcontatoreHammer() == 150) {
    m.setHammer(false);
    m.setJump(false);
  }
  if (((matrix[m.getY() / 16][m.getX() / 16 + 1] == 0 &&
        matrix[m.getY() / 16 + 1][m.getX() / 16 + 1] == 2) ||
       (matrix[m.getY() / 16][m.getX() / 16] == 0 &&
        matrix[m.getY() / 16 + 1][m.getX() / 16] == 2)) &&
      m.getScale()) {
    m.setScale(false);
    m.setFall(true);
    m.setUp(false);
  }
  if (m.getSpace() && m.getHammer())
    m.setSpace(false);
  if (m.getJump() && !m.getHammer()) {
    if (m.getSpace())
      m.setSpace(false);
    m.setJmp(m.getJmp() + 1);
    bmp = al_load_bitmap("../Sprites/Walk2.png");
    if (m.getRight()) {
      if (m.getJmp() < 3 && m.getX() != y * pixel - 16) {
        m.setY(m.getY() - 8);
        m.setX(m.getX() + 8);
      }
      al_draw_bitmap(bmp, m.getX(), m.getY(), ALLEGRO_FLIP_HORIZONTAL);
    } else if (m.getLeft()) {
      if (m.getJmp() < 3 &&
          m.getX() !=
              0) { /*togliere se si vuole lasciare in aria un solo frame*/
        m.setY(m.getY() - 8);
        m.setX(m.getX() - 8);
      }
      al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
    } else {
      if (m.getJmp() <
          3) /*togliere se si vuole lasciare in aria un solo frame*/
        m.setY(m.getY() - 8);
      if (m.getReverse())
        al_draw_bitmap(bmp, m.getX(), m.getY(), ALLEGRO_FLIP_HORIZONTAL);
      else
        al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
    }
    if (m.getJmp() >=
        3) { /*togliere se si vuole lasciare in aria un solo frame*/
      m.setJump(false);
    }
    m.setFall(true);
    al_destroy_bitmap(bmp);
  } else if (m.getFall() && m.getReverse()) {
    m.setUp(false);
    m.setDown(false);
    m.setJmp(m.getJmp() + 1);
    if (m.getSpace())
      m.setSpace(false);
    m.setY(m.getY() + 8);
    if (m.getRight() && m.getX() != (y * 16) - 16 &&
        (m.getJmp() == 4 || m.getJmp() == 5 || m.getJmp() == 6)) {
      m.setX(m.getX() + 8);
      m.setRight(false);
    } else if (m.getLeft() && m.getX() != 0 &&
               (m.getJmp() == 4 || m.getJmp() == 5 || m.getJmp() == 6)) {
      m.setX(m.getX() - 8);
      m.setLeft(false);
    }
    m.Draw(true);
    if ((m.getY() % 16 == 0 && matrix[m.getY() / 16 + 1][m.getX() / 16] == 1) ||
        (m.getX() % 16 != 0 &&
         matrix[m.getY() / 16 + 1][m.getX() / 16 + 1] == 1)) {
      m.setFall(false);
      m.setJmp(0);
    }
  } else if (m.getFall() && m.getReverse() == false) {
    m.setJmp(m.getJmp() + 1);
    if (m.getSpace())
      m.setSpace(false);
    m.setY(m.getY() + 8);
    if (m.getRight() && m.getX() != (y * 16) - 16 &&
        (m.getJmp() == 4 || m.getJmp() == 5 || m.getJmp() == 6)) {
      m.setX(m.getX() + 8);
      m.setRight(false);
    } else if (m.getLeft() && m.getX() != 0 &&
               (m.getJmp() == 4 || m.getJmp() == 5 || m.getJmp() == 6)) {
      m.setX(m.getX() - 8);
      m.setLeft(false);
    }
    m.Draw(false);
    if (matrix[m.getY() / 16 + 1][m.getX() / 16] == 1 ||
        (m.getX() % 16 != 0 &&
         matrix[m.getY() / 16 + 1][m.getX() / 16 + 1] == 1)) {
      m.setScale(false);
      m.setFall(false);
      m.setJmp(0);
    }
  } else if (m.getSpace() && !m.getHammer()) {
    m.setSpace(false);
    if (m.getFall() == false && m.getJump() == false) {
      m.setJump(true);
      if (m.getReverse()) {
        if (m.getRight() && m.getX() != (y * 16) - 16) {
          m.setY(m.getY() - 8);
          m.setX(m.getX() + 8);
        } else
          m.setY(m.getY() - 8);
        bmp = al_load_bitmap("../Sprites/Walk2.png");
        al_draw_bitmap(bmp, m.getX(), m.getY(), ALLEGRO_FLIP_HORIZONTAL);
      } else {
        if (m.getLeft() && m.getX() != 0) {
          m.setY(m.getY() - 8);
          m.setX(m.getX() - 8);
        } else
          m.setY(m.getY() - 8);
        bmp = al_load_bitmap("../Sprites/Walk2.png");
        al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
      }
      al_destroy_bitmap(bmp);
    }
  } else if (m.getRight() && m.getFall() == false &&
             !m.getScale() /*togliere se si vuole muovere nelle scale*/) {
    m.setReverse(true);
    if (m.getX() !=
        (y * 16) - 16 /*&&m.getY()%16==0*/) /*DIVERSO DA FINE SCHERMO*/ {
      if (m.getY() % 16 == 0 && matrix[m.getY() / 16 + 1][m.getX() / 16] == 1 &&
          m.getScale())
        m.setScale(false);
      if (!m.getScale() && !m.getHammer()) {
        m.setX(m.getX() + 8);
        m.setCont(m.getCont() + 1);
        if (m.getCont() == 1)
          bmp = al_load_bitmap("../Sprites/Walk1.png");
        else {
          bmp = al_load_bitmap("../Sprites/Walk2.png");
          m.setCont(0);
        }
      } else if (m.getScale() && !m.getHammer()) {
        m.setX(m.getX() + 8);
        m.setCont(m.getCont() + 1);
        if (m.getCont() == 1)
          bmp = al_load_bitmap("../Sprites/Climbing1.png");
        else {
          bmp = al_load_bitmap("../Sprites/Climbing2.png");
          m.setCont(0);
        }
      } else {
        m.setX(m.getX() + 8);
        m.setCont(m.getCont() + 1);
        if (m.getCont() == 1)
          bmp = al_load_bitmap("../Sprites/Hammer3.png");
        else {
          bmp = al_load_bitmap("../Sprites/Hammer4.png");
          m.setCont(0);
        }
      }
      if (m.getCont() != 0) {
        if (!m.getHammer())
          al_draw_bitmap(bmp, m.getX(), m.getY(), ALLEGRO_FLIP_HORIZONTAL);
        else
          al_draw_bitmap(bmp, m.getX(), m.getY() - 8, ALLEGRO_FLIP_HORIZONTAL);
      } else {
        if (!m.getHammer())
          al_draw_bitmap(bmp, m.getX(), m.getY(), ALLEGRO_FLIP_HORIZONTAL);
        else
          al_draw_bitmap(bmp, m.getX(), m.getY(), ALLEGRO_FLIP_HORIZONTAL);
      }
      if ((m.getX() % 16 == 0 &&
           matrix[(m.getY() / 16) + 1][m.getX() / 16] == 0) ||
          (m.getY() % 16 != 0 &&
           matrix[m.getY() / 16 + 1][m.getX() / 16] == 1 &&
           matrix[m.getY() / 16][m.getX() / 16] == 0 &&
           matrix[m.getY() / 16 + 2][m.getX() / 16] == 0)) {
        m.setFall(true);
        if (m.getScale())
          m.setScale(false);
      }
      al_destroy_bitmap(bmp);
    } else if (m.getX() == (y * 16) - 16)
      m.Draw(true);
    m.setRight(false);
  } else if (m.getLeft() && m.getFall() == false &&
             !m.getScale() /*togliere se si vuole muovere nelle scale*/) {
    m.setReverse(false);
    if (m.getX() !=
        0 /*&&m.getY()%16==0*/) /*DIVERSO DA FINE SCHERMO SINISTRO*/ {
      if (m.getY() % 16 == 0 && matrix[m.getY() / 16 + 1][m.getX() / 16] == 1 &&
          m.getScale())
        m.setScale(false);
      if (!m.getScale() && !m.getHammer()) {
        m.setX(m.getX() - 8);
        m.setCont(m.getCont() + 1);
        if (m.getCont() == 1)
          bmp = al_load_bitmap("../Sprites/Walk1.png");
        else {
          bmp = al_load_bitmap("../Sprites/Walk2.png");
          m.setCont(0);
        }
      } else if (m.getScale() && !m.getHammer()) {
        m.setX(m.getX() - 8);
        m.setCont(m.getCont() + 1);
        if (m.getCont() == 1)
          bmp = al_load_bitmap("../Sprites/Climbing1.png");
        else {
          bmp = al_load_bitmap("../Sprites/Climbing2.png");
          m.setCont(0);
        }
      } else {
        m.setX(m.getX() - 8);
        m.setCont(m.getCont() + 1);
        if (m.getCont() == 1)
          bmp = al_load_bitmap("../Sprites/Hammer3.png");
        else {
          bmp = al_load_bitmap("../Sprites/Hammer4.png");
          m.setCont(0);
        }
      }
      if ((m.getX() % 16 == 0 &&
           matrix[(m.getY() / 16) + 1][m.getX() / 16] == 0) ||
          (m.getX() % 16 == 0 && m.getY() % 16 != 0 &&
           matrix[m.getY() / 16][m.getX() / 16] == 0 &&
           matrix[m.getY() / 16 + 1][m.getX() / 16] == 1 &&
           matrix[m.getY() / 16 + 2][m.getX() / 16] == 0)) {
        m.setFall(true);
        if (m.getScale())
          m.setScale(false);
      }
      if (m.getCont() != 0) {
        if (!m.getHammer())
          al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
        else
          al_draw_bitmap(bmp, m.getX() + 16, m.getY() - 8, 0);
      } else {
        if (!m.getHammer())
          al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
        else
          al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
      }
      al_destroy_bitmap(bmp);
    } else if (m.getX() == 0)
      m.Draw(false);
    m.setLeft(false);
  } else if (m.getScale() && matrix[m.getY() / 16][m.getX() / 16] == 0 &&
             (matrix[(m.getY() / 16) + 1][(m.getX() / 16) - 1] == 2 ||
              (matrix[(m.getY() / 16) + 1][(m.getX() / 16) + 1] == 2 &&
               m.getX() % 16 == 0) ||
              matrix[(m.getY() / 16) + 1][m.getX() / 16] == 2)) {
    m.setFall(true);
    m.setUp(false);
  } else if ((m.getUp() && !m.getFall() && !m.getHammer())) {
    if ((((matrix[m.getY() / 16][m.getX() / 16] == 2 ||
           matrix[m.getY() / 16][m.getX() / 16] == 1) &&
          m.getX() % 16 == 0) ||
         (m.getY() % 16 != 0 && matrix[m.getY() / 16 + 1][m.getX() / 16] == 1) /*|| (matrix[(m.getY()+8)/16][m.getX()/16]==2 || matrix[(m.getY()+8)/16][m.getX()/16]==1))||(m.getX()%16!=0&&((matrix[m.getY()/16][m.getX()/16+1]==2 || matrix[m.getY()/16][m.getX()/16+1]==1)   || (matrix[(m.getY()+8)/16][m.getX()/16+1]==2 || matrix[(m.getY()+8)/16][m.getX()/16+1]==1))*/)) {
      m.setScale(true);
      if (m.getScale()) {
        m.setY(m.getY() - 8);
        m.setCont(m.getCont() + 1);
        if (m.getCont() == 1)
          bmp = al_load_bitmap("../Sprites/Climbing1.png");
        else {
          bmp = al_load_bitmap("../Sprites/Climbing2.png");
          m.setCont(0);
        }
        al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
        al_destroy_bitmap(bmp);
      }
    } else {
      if (m.getReverse())
        m.Draw(true);
      else
        m.Draw(false);
    }
    m.setUp(false);
  } else if (m.getDown() && !m.getFall() && !m.getHammer() && m.getX() % 16 == 0 /*togliere se si vuole fare andare dai lati delle scale in discesa*/) {
    if ((matrix[m.getY() / 16][m.getX() / 16] == 2 &&
         matrix[m.getY() / 16 + 1][m.getX() / 16] != 1) ||
        (matrix[m.getY() / 16][m.getX() / 16] == 0 &&
         matrix[m.getY() / 16 + 1][m.getX() / 16] == 1 &&
         matrix[m.getY() / 16 + 2][m.getX() / 16] == 2) ||
        (matrix[m.getY() / 16][m.getX() / 16] == 1 &&
         matrix[m.getY() / 16 + 1][m.getX() / 16] == 2) ||
        (matrix[m.getY() / 16][m.getX() / 16 + 1] == 2 &&
         matrix[m.getY() / 16 + 1][m.getX() / 16 + 1] != 1) ||
        (m.getX() % 16 != 0 && matrix[m.getY() / 16][m.getX() / 16 + 1] == 0 &&
         matrix[m.getY() / 16 + 1][m.getX() / 16 + 1] == 1 &&
         matrix[m.getY() / 16 + 2][m.getX() / 16 + 1] == 2) ||
        ((matrix[m.getY() / 16][m.getX() / 16 + 1] == 1 &&
          matrix[m.getY() / 16 + 1][m.getX() / 16 + 1] == 2) &&
         m.getX() % 16 != 0)) {
      m.setScale(true);
      // se non ci si vuole muovere destra sinistra
      m.setRight(false); // messi per impedire che restino in memoria i
                         // movimenti
      m.setLeft(false);
      // fine
      m.setY(m.getY() + 8);
      m.setCont(m.getCont() + 1);
      if (m.getCont() == 1)
        bmp = al_load_bitmap("../Sprites/Climbing1.png");
      else {
        bmp = al_load_bitmap("../Sprites/Climbing2.png");
        m.setCont(0);
      }
      al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
      al_destroy_bitmap(bmp);
    } else {
      if (m.getReverse())
        m.Draw(true);
      else
        m.Draw(false);
    }
    m.setDown(false);
  } else if (m.getScale()) {
    // se non ci si vuole muovere destra sinistra
    m.setRight(false); // messi per impedire che restino in memoria i movimenti
    m.setLeft(false);
    // fine
    if (m.getY() % 16 == 0 && matrix[m.getY() / 16][m.getX() / 16] == 2 &&
        matrix[(m.getY() / 16) + 1][m.getX() / 16] == 1) {
      m.setScale(false);
      if (m.getReverse())
        m.Draw(true);
      else
        m.Draw(false);
    } else if (m.getY() % 16 == 0 &&
               matrix[m.getY() / 16][m.getX() / 16] == 0 &&
               matrix[(m.getY() / 16) + 1][m.getX() / 16] == 1) {
      m.setScale(false);
      if (m.getReverse())
        m.Draw(true);
      else
        m.Draw(false);
    } else if (m.getCont() == 1) {
      bmp = al_load_bitmap("../Sprites/Climbing1.png");
      al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
    } else {
      bmp = al_load_bitmap("../Sprites/Climbing2.png");
      m.setCont(0);
      al_draw_bitmap(bmp, m.getX(), m.getY(), 0);
    }
  } else if (m.getReverse())
    m.Draw(true);
  else
    m.Draw(false);
  if ((matrix[m.getY() / 16][(m.getX() / 16) - 1] == 2 ||
       matrix[m.getY() / 16][(m.getX() / 16) + 1] == 2 ||
       matrix[m.getY() / 16][m.getX() / 16] == 2) &&
      m.getY() == 0) {
    setMap(m, dk);
    win = true;
  }
  if (matrix[m.getY() / 16][(m.getX() / 16)] == 6) {
    bonus = true;
    setMap(m, dk);
    win = true;
  }
  al_set_target_backbuffer(this->display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, (y * pixel), (x * pixel), scale_x,
                        scale_y, scale_w, scale_h, 0);
}

bool Graphic::getWin() { return win; }

void Graphic::setWin(bool ok) { win = ok; }

bool Graphic::getBonus() { return bonus; }

bool Graphic::getDeath() { return death; }

void Graphic::setDeath(bool ok) { death = ok; }

void Graphic::setMap(Mario &m, DonkeyKong &dk) {
  if (bonus && level != 9)
    level = 8;
  if (bonus && level == 9) {
    level = 0;
    bonus = false;
  }
  if (!bonus && level == 8) {
    level = 0;
  }
  level++;
  fstream input;
  input.open(
      ((string) "../Maps/") +
      (((string) "Map") + (to_string(level)) + ((string) ".map")).c_str());
  if (input.is_open())
    input >> x >> y;
  if (input.is_open())
    for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
        input >> matrix[i][j];
  input.close();
  if (!fires.empty())
    fires.clear();
  setDk(dk);
  setMario(m);
  barrels.clear();
}
void Graphic::setThisMap(Mario &m) {
  fstream input;
  input.open(
      ((string) "../Maps/") +
      (((string) "Map") + (to_string(level)) + ((string) ".map")).c_str());
  if (input.is_open())
    input >> x >> y;
  if (input.is_open())
    for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
        input >> matrix[i][j];
  input.close();
  setMario(m);
  barrels.clear();
}

void Graphic::drawLife(int life) {
  al_set_target_bitmap(buffer);
  const char *a = to_string(life).c_str();
  al_draw_ustr(font, al_map_rgb(44, 117, 255), (y * pixel) / 2 + (8 * pixel),
                10, 0, al_ustr_new("\u2764 ") );
  al_draw_textf(font, al_map_rgb(44, 117, 255), (y * pixel) / 2 + (9 * pixel),
                10, 0, "%d", life);

  al_set_target_backbuffer(this->display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, (y * pixel), (x * pixel), scale_x,
                        scale_y, scale_w, scale_h, 0);
}
void Graphic::drawScore(const int &score) {
  al_set_target_bitmap(buffer);
  const char *a = to_string(score).c_str();
  al_draw_textf(font, al_map_rgb(0, 0, 0), (y * pixel) / 2 + (8 * pixel), 10, 0,
                "Bonus: ");
  al_draw_textf(font, al_map_rgb(0, 0, 0), (y * pixel) / 2 + (9 * pixel), 10, 0,
                "%d", score);

  al_set_target_backbuffer(this->display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, (y * pixel), (x * pixel), scale_x,
                        scale_y, scale_w, scale_h, 0);
}
Graphic::~Graphic() {}
