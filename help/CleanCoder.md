S Bandi's Notes from The Clean Coder
================================
Notes from book [The Clean Coder](https://www.goodreads.com/book/show/10284614-the-clean-coder)
*Author* : Robert C. Martin (`Uncle Bob`) 

## Professionalism
* Do NO harm to both the Function and structure of the software
* Responsibility for imperfections
    * Releasing the code to QA that you don’t know works is unprofessional.
    * You must know it Works before you commit or merge into develop branch.
* Merciless refactoring : Lightweight changes to the module to improve its structure whenever there is opportunity

## Saying No
* The earlier you raise the flag to all stakeholders, the more likely there will be time for the team to stop, reassess the current actions being taken, and decide if something can be done or changed (in terms of priorities, for example). By doing this, your commitment can still be fulfilled, or you can change to a different commitment.
* The most important time to say NO is when the stakes are highest. 
* One important point here is: If you don’t tell anyone about the potential problem as soon as possible, you’re not giving anyone a chance to help you follow through on your commitment.

## Saying Yes
* Professionals are not required to say yes to everything that is asked of them. However, they should work hard to find creative ways to make `yes` possible. When professionals say yes, they use the language of commitment so that there is no doubt about what they’ve promised.

## Coding
* Develop Confidence and Error-Sense
    * If you are tired or distracted, do not code. You’ll only wind up redoing what you did. Instead, find a way to eliminate the distractions and settle your mind
Don’t write code when you are tired. Dedication and professionalism are more about discipline than hours. Make sure that your sleep, health, and lifestyle are tuned so that you can put in eight good hours per day
* *Worry Code* : Ideally the time spent wrestling with personal issues would be personal time. It would be a shame to spend an hour at the office this way. Professional developers allocate their personal time in order to ensure that the time spent at the office is as productive as possible. That means you should specifically set aside time at home to settle your anxieties so that you don’t bring them to the office.
On the other hand, if you find yourself at the office and the background anxieties are sapping your productivity, then it is better to spend an hour quieting them than to use brute force to write code that you’ll just have to throw away later (or worse, live with)
* *Interruptions* : There will be interruptions that distract you and cause you to lose time. When they happen, remember that next time you may be the one who needs to interrupt someone else. So the professional attitude is a polite willingness to be helpful
* *Creativity breeds creativity* : I find that I am most creative when I am exposed to other people’s creativity. So I read lots of science fiction. The creativity of those authors somehow stimulates my own creative juices for software.
* *collaboration* : Yes, this is a stereotype. Yes, it is generalization with many exceptions. But the reality is that programmers do not tend to be collaborators. And yet collaboration is critical to effective programming. Therefore, since for many of us collaboration is not an instinct, we require disciplines that drive us to collaborate.
* It is unprofessional to remain stuck when help is easily accessible.

## Test Driven Development
* *Design For Testability* : Design your code to be easy to test
    * The problem with testing code is that you have to isolate that code. It is often difficult to test a function if that function calls other functions. To write that test you’ve got to figure out some way to decouple the function from all the others. In other words, the need to test first forces you to think about good design
* *Courage* :
    * Why don’t you fix bad code when you see it? Your first reaction upon seeing a messy function is “This is a mess, it needs to be cleaned.” Your second reaction is “I’m not touching it!” Why? Because you know that if you touch it you risk breaking it; and if you break it, it becomes yours.
    * This is one of the most powerful benefits of TDD. When you have a suite of tests that you trust, then you lose all fear of making changes. When you see bad code, you simply clean it on the spot. The code becomes clay that you can safely sculpt into simple and pleasing structures.
    * When programmers lose the fear of cleaning, they clean! And clean code is easier to understand, easier to change, and easier to extend. Defects become even less likely because the code gets simpler. And the code base steadily improves instead of the normal rotting that our industry has become used to.
* *The unit tests are documents* : They describe the lowest-level design of the system.
    * There will be a unit test that describes how to call every function in the system every way that those functions can meaningfully be called. For anything you need to know how to do, there will be a unit test that describes it in detail
* The upshot of all this is that TDD is the professional option. It is a discipline that enhances certainty, courage, defect reduction, documentation, and design. With all that going for it, it could be considered unprofessional not to use it

## Practicing
* Like any martial artist, a programmer should know several different kata and practice them regularly so that they don’t fade away from memory

## Acceptance Testing
* *Need of it?* : Both business and programmers are tempted to fall into the trap of premature precision. Business people want to know exactly what they are going to get before they authorize a project. Developers want to know exactly what they are supposed to deliver before they estimate the project. Both sides want a precision that simply cannot be achieved, and are often willing to waste a fortune trying to attain it.
* The purpose of acceptance tests is communication, clarity, and precision. By agreeing to them, the developers, stakeholders, and testers all understand what the plan for the system behavior is. Achieving this kind of clarity is the responsibility of all parties. Professional developers make it their responsibility to work with stakeholders and testers to ensure that all parties know what is about to be built
* *Automation* : Acceptance tests should always be automated. There is a place for manual testing elsewhere in the software lifecycle, but these kinds of tests should never be manual. The reason is simple: cost
* *Acceptance Tests versus Unit Tests*
    * Acceptance tests are not unit tests. Unit tests are written by programmers for programmers. They are formal design documents that describe the lowest level structure and behavior of the code. The audience is programmers, not business.
    * Acceptance tests are written by the business for the business (even when you, the developer, end up writing them). They are formal requirements documents that specify how the system should behave from the business’ point of view. The audience is the business and the programmers

## Estimation
* *The Law of Large Numbers* : Estimates are fraught with error. That’s why they are called estimates. One way of managing error is to take advantage of the Law of Large Numbers. An implication of this law is that if you break up a large task into many smaller tasks and estimate them independently, the sum of the estimates of the small tasks will be more accurate than a single estimate of the larger task. The reason for this increase in accuracy is that the errors in the small tasks tend to integrate out

## Pressure
* Imagine that you are having an out-of-body experience, observing yourself on an operating table while a surgeon performs open heart surgery on you. That surgeon is trying to save your life, but time is limited so he is operating under a deadline—a literal deadline.
    * How do you want that doctor to behave? Do you want him to appear calm and collected? …
    * Or do you want him sweating and swearing? …
* The professional developer is calm and decisive under pressure. As the pressure grows he adheres to his `training and disciplines/best practices`, knowing that they are the best way to meet the deadlines and commitments that are pressing on him.

