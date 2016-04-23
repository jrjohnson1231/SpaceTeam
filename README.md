ReadMe.md
=========

CHANGELOG
---------
-**2/16/16 Scary:** start and stop.  Hey guys!  I'm done with the start and stop commands! I commented them up for you.  Let me know what you think!

-**3/16/16 Scary:** Tensor. Hey guys.  I made a tensor class.  It's really basic, just data for x,y,z coordinates and a basic conversion to polar.

-**3/20/16 Allie:** Planets. Hey! I made a very basic class for planets. Right now all it can do is find the force between two bodies, and the acceleration of a body. More to come on that. I also added a function to Tensor that finds the distance between two bodies. maybe I should put that in the Planets class? Let me know!

-**3/20/16 John:** Tensor/Planets. Hey guys, the dynamic memory was giving us some issues in the Tensor class so I got rid of it because it wasn't entirely necessary. Also included the Tensor class into the Planet class with Allie.

-**3/30/16 John:** I overloaded some operators in the tensor class, making the operations in planet much, much simpler.

-**4/11/16 John:** Overall simplification of code in planet and tensor class. Created friendship between planet and tensor, as well as a static vector of all the planet pointers so that we can easily loop over all the planets we have made. Force function is probably the most changed aspect, and it is much simpler and loops over the vector instead of taking a planet as a parameter.

-**4/13/16 John:** I added a name member to planet to aid in display. I also updated the << operator for tensor to make it look nicer. *update()* is now static so one call from the driver updates all planets, and the driver takes command line argument dt.

-**4/14/16 Allie:** I updated the planets class into a new inheritance hierarchy with an abstract class called "Body" and classes "Planet" (which uses the gravitational force) and "Charged" (which uses the coulomb force). I also did a little bit of cleanup overall in structure and style. With the new hierarchy it makes it much easier to implement different force laws

-**4/21/16 John:** I started incorporating the Planet and Body classes into the graphic classes. I did moved all the displaying to the Window class, and added a planet to the Object class. The main function also uses the Planet::update() function to update the position and Window::update() has been renamed to display().

-**4/23/16 Allie:** Changed the planets and charges vectors to hold actual objects and not pointers to them. Created a collision function that deletes two planets if they collide. 

TODO
----
- animate simulation so we can find out what parts of planet/tensor need to be adjusted

Meetings
--------
- **2/16/16 6:00-7:00**: Discussed project details and sent email to Professor Emrich outlining our ideas.
- **2/17/16 9:30-10:20(in-class)**: Discussed in more detail class hierarchy as well as analytical difficulty of n-body problem.
- **2/29/16 3:00-4:00**: Monday Lab (Allie and John) Came up with rubric and discussed where to begin.
- **3/14/16 3:00-4:00**: Monday Lab (Allie and John) Started LazyFoo SDL tutorials.
- **3/16/16 2:00-3:00**: Will focus on calculating coordinates and displaying separately. Will worry about user input while the program is running later on once we have things moving correctly on the screen. *Next Week:* Plan on having individual parts completed to create two body motion. *Two Weeks:* Plan on getting at least two bodies moving on a screen. Chris will work on SDL while John and Allie will work on physics behind motion. Decided to start having weekly meetings.
- **3/20/16 8:30-10:00**: John and Allie met and worked on Planets class. We got it working with Tensor and with 2 bodies with no initial velocity (basically just 2 bodies flying towards each other). Our To-Do list is above.
- **3/31/16 11:00-11:30**: Group meeting. We discussed our next steps and the changes that we've made since our last meeting. John and Allie will work on adapting the planets class to work with initial velocities. Scary will work on getting SDL to work with the tensor class.
- **4/23/16 1:30-4:00**: Group meeting to work on the project. Spent a few hours just working together on fixing all the problems with the code. 