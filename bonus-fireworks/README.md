Name: Aayushi Dangol

userName1: adangol1

Lab Questionnaire

Approximately, how many hours did you take to complete this lab (provide your answer as a single integer on the line below).

6

How difficult did you find this lab? (1-5, with 5 being very difficult and 1 being very easy)

2

Describe the biggest challenge you faced on this lab.

Ubderstanding the difference between rockets and sparks.

What fucntions did you complete in this lab? 
(0.1 points) Implement AFlee:calculateDesiredVelocity
(0.2 points) Implement AArrival:calculateDesiredVelocity
(0.2 points) Implement ADeparture:calculateDesiredVelocity
(1.0 points) Implement AAvoid:calculateDesiredVelocity
(1.0 points) Implement AWander:calculateDesiredVelocity 

    (0.5 points) Implement AParticleSystem::update(). Each particle contains its current state (position and velocity), its derivatives, and other attributes, e.g.
        state[POS],
        state[VEL],
        derivative[POS],
        derivative[VEL],
        mass, and
        "time to live" (ttl). 

    In update, compute the derivative and update each particle's state. Additionally, decrement ttl by the delta time.
    (0.5 points) Implement ARocket::init() to initialize the rocket near the ground with a random upwards velocity. When you press the spacebar, you should now see the rocket.
    (0.5 points) Implement ASpark::init() to initialize the firework based on the given ARocket. To start position of each spark should be the rocket's current position. The velocity should extend outwards in a circle around the start position. To make a nicer effect, create several rings of sparks. Each ring will have a faster velocity than the one before it.
    (0.2) Add random colors to your fireworks. Extend AParticle to contain a color. You will need to edit ASpark::draw and ARocket::draw to see the change.
    (0.1) Make your sparks fade as they age. Extend AParticle to contain an alpha value. To see the effect, extend the draw functions as well as extend AParticleSystem::update to change the alpha value each frame.
    (0.1) Make your sparks grow over time. Extend AParticle to contain a scale. Extend update and draw to complete the feature.
    

