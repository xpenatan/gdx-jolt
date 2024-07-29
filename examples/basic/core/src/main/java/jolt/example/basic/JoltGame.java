package jolt.example.basic;

import com.badlogic.gdx.Game;

public class JoltGame extends Game {

    @Override
    public void create() {
        setScreen(new InitScreen(this));
    }
}