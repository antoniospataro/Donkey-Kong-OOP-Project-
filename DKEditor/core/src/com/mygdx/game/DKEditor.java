package com.mygdx.game;


import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class DKEditor extends ApplicationAdapter {
    SpriteBatch batch;
    Texture img0;
    Texture img1;
    Texture img2;
    Texture img3;
    int size;
    int x;
    int y;
    int width;
    int height;
    boolean one = true;
    boolean two = false;
    boolean three = false;
    boolean zero = false;
    int[][] matrix = new int[24][37];

    OrthographicCamera camera;
    File fw;
    StringBuffer s;
    BufferedWriter write;

    public void create() {
        this.batch = new SpriteBatch();
        this.s = new StringBuffer();
        this.img0 = new Texture("back.png");
        this.img1 = new Texture("Floor.png");
        this.img2 = new Texture("Scale.png");
        this.img3 = new Texture("Barrel0.png");
        this.size = 16;
        reset();
        this.camera = new OrthographicCamera(Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
        this.camera.setToOrtho(true, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
    }

    void reset() {
        for (int i = 0; i < this.matrix.length; i++) {
            for (int j = 0; j < this.matrix[i].length; j++) {
                if (i != 23) {
                    this.matrix[i][j] = 0;
                } else {
                    this.matrix[i][j] = 1;
                }
            }
        }
    }

    public void render() {
        Gdx.gl.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
        Gdx.gl.glClear(16384);
        this.camera.update();
        this.batch.setProjectionMatrix(this.camera.combined);

        this.batch.begin();
        draw();
        this.batch.end();

        reload();
        setDraw();
    }


    public void dispose() {
        try {
            if (this.write != null)
                this.write.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.batch.dispose();
        this.img1.dispose();
        this.img2.dispose();
        this.img3.dispose();
        this.img0.dispose();
    }

    public void draw() {
        for (int i = 0; i < this.matrix.length; i++) {
            for (int j = 0; j < this.matrix[i].length; j++) {
                if (this.matrix[i][j] == 1)
                    this.batch.draw(this.img1, (16 * j), (16 * i));
                if (this.matrix[i][j] == 2)
                    this.batch.draw(this.img2, (16 * j), (16 * i));
                if (this.matrix[i][j] == 3)
                    this.batch.draw(this.img3, (16 * j), (16 * i));
                if (this.matrix[i][j] == 0)
                    this.batch.draw(this.img0, (16 * j), (16 * i));
            }
        }
    }

    public void reload() {
        this.y = Gdx.input.getY() / this.size;
        this.x = Gdx.input.getX() / this.size;
        if (Gdx.input.getX() < 37 * this.size - 1 && Gdx.input.getX() > 0 && Gdx.input.getY() > 0 && Gdx.input.getY() < 24 * this.size - 1 &&
                Gdx.input.isTouched())
            if (this.one) {
                this.matrix[this.y][this.x] = 1;
            } else if (this.two) {
                this.matrix[this.y][this.x] = 2;
            } else if (this.three) {
                this.matrix[this.y][this.x] = 3;
            } else if (this.zero) {
                this.matrix[this.y][this.x] = 0;
            }
        if (Gdx.input.isKeyJustPressed(47)) {
            try {
                this.fw = new File("BonusLevel.map");
                if (this.fw.exists())
                    this.fw.delete();
                this.write = new BufferedWriter(new FileWriter("BonusLevel.map"));
            } catch (IOException e) {
                e.printStackTrace();
                System.out.println("errore");
            }
            this.s.append(24);
            this.s.append(" ");
            this.s.append(37);
            try {
                this.write.write(this.s.toString());
                this.write.newLine();
                this.s.delete(0, this.s.length());
                for (int i = 0; i < this.matrix.length; i++) {
                    for (int j = 0; j < this.matrix[i].length; j++) {
                        this.s.append(this.matrix[i][j]);
                        this.s.append(" ");
                    }
                    this.write.write(this.s.toString());
                    this.write.newLine();
                    this.s.delete(0, this.s.length());
                }

            } catch (IOException e) {
                e.printStackTrace();
                System.out.println("errore2");
            }
        }
    }

    void setDraw() {
        if (Gdx.input.isKeyJustPressed(8)) {
            this.one = true;
            this.two = false;
            this.three = false;
            this.zero = false;
        } else if (Gdx.input.isKeyJustPressed(9)) {
            this.two = true;
            this.one = false;
            this.three = false;
            this.zero = false;
        } else if (Gdx.input.isKeyJustPressed(10)) {
            this.three = true;
            this.one = false;
            this.two = false;
            this.zero = false;
        } else if (Gdx.input.isKeyJustPressed(7)) {
            this.zero = true;
            this.three = false;
            this.one = false;
            this.two = false;
        } else if (Gdx.input.isKeyJustPressed(46)) {
            this.one = true;
            this.two = false;
            this.three = false;
            this.zero = false;
            reset();
        }
    }

    public void write() {
        for (int i = 0; i < this.matrix.length; i++) {
            for (int j = 0; j < this.matrix[i].length; j++)
                System.out.print(this.matrix[i][j] + " ");
        }
    }
}
