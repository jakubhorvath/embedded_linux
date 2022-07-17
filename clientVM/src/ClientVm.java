import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class ClientVm {
    public static void main(String argv[]) throws Exception {
        String sentence_from_server;

        //Tạo socket cho client kết nối đến server qua ID address và port number
        Socket clientSocket = new Socket("127.0.0.1", 5000);

        //Tạo OutputStream nối với Socket
        DataOutputStream outToServer =
                new DataOutputStream(clientSocket.getOutputStream());

        //Tạo inputStream nối với Socket
        BufferedReader inFromServer =
                new BufferedReader(new
                        InputStreamReader(clientSocket.getInputStream()));

        outToServer.writeBytes("sendToServer");

        //Đọc tin từ Server thông qua InputSteam đã nối với socket
        sentence_from_server = inFromServer.readLine();

        //print kết qua ra màn hình
        System.out.println("FROM SERVER: " + sentence_from_server);


        int choice = -1;
        do {
            int vmNumber = chooseVmOption();
            System.out.println("----------------------------------------------------------------");

            List<String> listProducts = getProduct(vmNumber);

            int product = chooseProduct(listProducts);
            System.out.println("----------------------------------------------------------------");

            int numberOfProduct = numberOfProduct();
            System.out.println("----------------------------------------------------------------");

            System.out.println("you are choosing:");
            System.out.println("Vending Maching: "+ vmNumber);
            System.out.println("product : "+listProducts.get(product));
            System.out.println("numberOfProduct : "+numberOfProduct);

            String sendToServer = "vm "+vmNumber+" "+listProducts.get(product)+" "+numberOfProduct;
            //Gửi chuỗi ký tự tới Server thông qua outputStream đã nối với Socket (ở trên)
            outToServer.writeBytes(sendToServer);

            //Đọc tin từ Server thông qua InputSteam đã nối với socket
            sentence_from_server = inFromServer.readLine();

            //print kết qua ra màn hình
            System.out.println("FROM SERVER: " + sentence_from_server);


            System.out.println("----------------------------------------------------------------");
            Scanner keyboard = new Scanner(System.in);
            System.out.print("Enter 0 if you want to buy something else: ");
            choice = keyboard.nextInt();



        } while (choice == 0);


    }


    public static int chooseVmOption() {
        int choose = 0;
        System.out.println("Vending Machine 1: enter 1");
        System.out.println("Vending Machine 2: enter 2");
        System.out.println("Vending Machine 2: enter 3");
        do {
            Scanner keyboard = new Scanner(System.in);
            System.out.print("enter right option : ");
            choose = keyboard.nextInt();
        } while (choose < 1 || choose > 3);
        System.out.println("you are choosing : vending machine " + choose);
        return choose;
    }

    public static int chooseProduct(List<String> list) {
        System.out.println("option product");
        int choose = 0;
        for (int i = 0; i < list.size(); i++) {
            int j=i+1;
            System.out.println(j+" "+list.get(i));
        }
        do {
            Scanner keyboard = new Scanner(System.in);
            System.out.print("enter right product number : ");
            choose = keyboard.nextInt();
        } while (choose < 1 || choose > list.size());
        System.out.println("you are choosing :" + list.get(choose-1));
        return choose-1;
    }


    public static int numberOfProduct() {
        int number = 0;
        System.out.print("Enter the number of product :");
        do {
            Scanner keyboard = new Scanner(System.in);
            number = keyboard.nextInt();
        } while (number < 1);
        return number;
    }

    public static List<String> getProduct(int vm) throws FileNotFoundException {


        String url ="C:\\Users\\lenovo\\Downloads\\Lab01\\linux\\embedded_linux\\clientVM\\src\\machineInventory" + vm + ".txt";
        FileInputStream fileInputStream = new FileInputStream(url);
        Scanner scanner = new Scanner(fileInputStream);
        int i=0;
        List<String> products = new ArrayList<String>();
        while (scanner.hasNextLine()) {
            String s = scanner.nextLine();

            if (i>0){
                String[] parts = s.split(" ");
                products.add(parts[1]);
            }
            i++;

        }

        return products;

    }


}
