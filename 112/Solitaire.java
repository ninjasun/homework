package solitaire;

class Solitaire {
	package solitaire;

	import java.io.IOException;
	import java.util.Scanner;
	import java.util.Random;
	import java.util.NoSuchElementException;

	/**
	 * This class implements a simplified version of Bruce Schneier's Solitaire Encryption algorithm.
	 * 
	 * @author RU NB CS112
	 */
	public class Solitaire {
		
		/**
		 * Circular linked list that is the deck of cards for encryption
		 */
		CardNode deckRear;
		
		/**
		 * Makes a shuffled deck of cards for encryption. The deck is stored in a circular
		 * linked list, whose last node is pointed to by the field deckRear
		 */
		public void makeDeck() {
			// start with an array of 1..28 for easy shuffling
			int[] cardValues = new int[28];
			// assign values from 1 to 28
			for (int i=0; i < cardValues.length; i++) {
				cardValues[i] = i+1;
			}
			
			// shuffle the cards
			Random randgen = new Random();
	 	        for (int i = 0; i < cardValues.length; i++) {
		            int other = randgen.nextInt(28);
		            int temp = cardValues[i];
		            cardValues[i] = cardValues[other];
		            cardValues[other] = temp;
		        }
		     
		    // create a circular linked list from this deck and make deckRear point to its last node
		    CardNode cn = new CardNode();
		    cn.cardValue = cardValues[0];
		    cn.next = cn;
		    deckRear = cn;
		    for (int i=1; i < cardValues.length; i++) {
		    	cn = new CardNode();
		    	cn.cardValue = cardValues[i];
		    	cn.next = deckRear.next;
		    	deckRear.next = cn;
		    	deckRear = cn;
		    }
		}
		
		/**
		 * Makes a circular linked list deck out of values read from scanner.
		 */
		public void makeDeck(Scanner scanner) 
		throws IOException {
			CardNode cn = null;
			if (scanner.hasNextInt()) {
				cn = new CardNode();
			    cn.cardValue = scanner.nextInt();
			    cn.next = cn;
			    deckRear = cn;
			}
			while (scanner.hasNextInt()) {
				cn = new CardNode();
		    	cn.cardValue = scanner.nextInt();
		    	cn.next = deckRear.next;
		    	deckRear.next = cn;
		    	deckRear = cn;
			}
		}
		
		/**
		 * Implements Step 1 - Joker A - on the deck.
		 */
		void jokerA() {
			// COMPLETE THIS METHOD
			int temp;
			CardNode ptr = this.deckRear;
			//CardNode rear = ptr;
			
			while (ptr.cardValue != 27)
			{
				ptr = ptr.next;
			}
			
			temp = ptr.cardValue;
			ptr.cardValue = ptr.next.cardValue;
			ptr.next.cardValue = temp;
			
			//this.deckRear = rear;
		}
		
		/**
		 * Implements Step 2 - Joker B - on the deck.
		 */
		void jokerB() {
		    // COMPLETE THIS METHOD
			
			int temp;
			CardNode ptr = this.deckRear;
			
			while (ptr.cardValue != 28)
			{
				ptr = ptr.next;
			}
			
			temp = ptr.cardValue;
			ptr.cardValue = ptr.next.next.cardValue;
			ptr.next.next.cardValue = temp;
			
			temp = ptr.cardValue;
			ptr.cardValue = ptr.next.cardValue;
			ptr.next.cardValue = temp;

		}
		
		/**
		 * Implements Step 3 - Triple Cut - on the deck.
		 */
		void tripleCut() {
			// COMPLETE THIS METHOD	
			CardNode ptr = this.deckRear.next;
			CardNode p1,p2,p3,p4,p5,p6,p7;
			
			//if first two cards are both jokers
			if ( (ptr.cardValue == 27 || ptr.cardValue == 28) &&
					(ptr.next.cardValue == 27 || ptr.next.cardValue == 28) )
			{
				ptr = ptr.next;
				this.deckRear = ptr;
				return;
			}
			
			//if first card is joker but second card is not. 
			if (ptr.cardValue == 27 || ptr.cardValue == 28)
			{
				ptr = ptr.next;
				while (ptr.cardValue != 27 || ptr.cardValue != 28)
				{
					ptr = ptr.next;
				}
				
				this.deckRear = ptr;
				return;
			}
			
			while (ptr.next.cardValue != 27 || ptr.next.cardValue != 28)
			{
				ptr = ptr.next;
			}
			p1 = ptr; //location before first joker
			p2 = ptr.next; //location of first joker.
			p3 = ptr.next.next; //location after first joker
			ptr = ptr.next;
			
			while (ptr.next.cardValue != 27 || ptr.next.cardValue != 28)
			{
				ptr = ptr.next;
			}		
			p4 = ptr; //location before second joker
			p5 = ptr.next; // location of second joker
			p6 = ptr.next.next; //location after second joker
			
			ptr = this.deckRear;
			p7 = ptr; //location of last card
			while (p7.next != ptr)
			{
				p7 = p7.next;
			}
			
			p7.next = p2;
			p5.next = ptr;
			p1.next = p6;
			this.deckRear = p1;
		}
		
		/**
		 * Implements Step 4 - Count Cut - on the deck.
		 */
		void countCut() {		
			// COMPLETE THIS METHOD
			CardNode ptr = this.deckRear;
			CardNode rear = ptr;
			CardNode beforeLast = ptr;
			CardNode last, p1, p2;
			int count;
			p1 = ptr;
			
			while (ptr.next != rear)
			{
				ptr = ptr.next;
				if (ptr.next == rear)
				{
					beforeLast = ptr;
				}
			}
			last = beforeLast.next;
			
			count = ptr.cardValue;
			ptr = this.deckRear;
			
			if (count == 28)
			{
				count = 27;
			}
			
			for (int i = 0; i < count; i++)
			{
				p1 = ptr;
				ptr = ptr.next;
			}
			p2 = ptr;
			ptr = this.deckRear;
			
			
			p1.next = last;
			last.next = p2;
			beforeLast.next = this.deckRear;
			
			this.deckRear = p2;
		}
		
		/**
		 * Utility method that prints a circular linked list, given its rear pointer
		 * 
		 * @param rear Rear pointer
		 */
		private static void printList(CardNode rear) {
			if (rear == null) { 
				return;
			}
			System.out.print(rear.next.cardValue);
			CardNode ptr = rear.next;
			do {
				ptr = ptr.next;
				System.out.print("," + ptr.cardValue);
			} while (ptr != rear);
			System.out.println("\n");
		}

		/**
		 * Implements Step 5 - key = INCLUDING repeating the whole process if the key turns
		 * out to be a joker.
		 * 
		 * @return Key between 1 and 26
		 */
		
		private int keyGen()
		{
			CardNode ptr = this.deckRear;
			int value = ptr.cardValue;
			int answer;
			
			if (value == 28)
			{
				value = 27;
			}
			
			for (int i =0; i < value; i++)
			{
				ptr = ptr.next;
			}
			answer = ptr.next.cardValue;
			
			if (ptr.next.cardValue == 27 || 
				ptr.next.cardValue == 28)
			{
				this.countCut();
				answer = this.keyGen();
			}
			
			return answer;

		}
		int getKey() {
			// COMPLETE THIS METHOD
			this.jokerA();
			this.jokerB();
			this.tripleCut();
			this.countCut();
			int answer = this.keyGen();
			
			return answer;
			/*
			CardNode ptr = this.deckRear;
			int value = ptr.cardValue;
			int answer;
			
			if (value == 28)
			{
				value = 27;
			}
			
			for (int i =0; i < value; i++)
			{
				ptr = ptr.next;
			}
			answer = ptr.next.cardValue;
			
			if (ptr.next.cardValue == 27 || 
				ptr.next.cardValue == 28)
			{
				this.countCut();
				answer = this.getKey();
			}
			
			return answer;
			*/
		}
		
		/**
		 * Encrypts a message, ignores all characters except upper case letters
		 * 
		 * @param message Message to be encrypted
		 * @return Encrypted message, a sequence of upper case letters only
		 */
		public String encrypt(String message) {	
			// COMPLETE THIS METHOD
		    String input = message;
		    char current;
		    int key;
		    String answer = "";
		    
		    while (input.length() > 0)
		    {
		    	current = input.charAt(0);
		    	key = this.getKey();
		    	current = (char) (current + key);
		    	if (current + key > 26)
		    	{
		    		current = (char) (current - 26);
		    	}
		    	
		    	answer = answer + current;
		    	input = input.substring(1);
		    }
		    return answer;
		}
		
		/**
		 * Decrypts a message, which consists of upper case letters only
		 * 
		 * @param message Message to be decrypted
		 * @return Decrypted message, a sequence of upper case letters only
		 */
		public String decrypt(String message) {	
			// COMPLETE THIS METHOD
		    // THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
		    String answer = this.encrypt("DUDEWHERESMYCAR"); 
		    System.out.println(answer);
		    return answer;
		}
	}

}
