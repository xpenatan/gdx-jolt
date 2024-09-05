package jolt.example.samples.app;

import jolt.example.samples.app.tests.BoxShapeTest;

public class SamplesApp {

    Test test;

    public void setup() {

    }

    public void update(float delta) {
        if(test != null) {
            test.update(delta);
        }
    }

    public void startTest(Class<? extends Test> testClass) {
        if(test != null) {
            test.dispose();
            test = null;
        }
        test = new BoxShapeTest();
        test.setup();
    }

    public void nextTest() {

    }
}