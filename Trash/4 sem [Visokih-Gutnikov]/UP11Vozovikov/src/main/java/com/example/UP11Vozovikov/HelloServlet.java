package com.example.UP11Vozovikov;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.annotation.*;

@WebServlet(name = "helloServlet", value = "/hello-servlet")
public class HelloServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        PrintWriter out = resp.getWriter();

        String font_size = req.getParameter("font_size");
        String string_amount = req.getParameter("string_amount");

        int amount;
        try {
            Integer.parseInt(font_size);
            amount = Integer.parseInt(string_amount);
        } catch (Exception ex) {
            out.println("<p>Wrong input values! Please, try again.</p>");
            return;
        }
        List<String> list_ = new ArrayList<>();
        InputStream input = new FileInputStream("C:\\Users\\User01\\Desktop\\Labs\\LabsFour\\UP11Vozovikov\\src\\main\\resources\\file.txt");
        BufferedReader buf = new BufferedReader(new InputStreamReader(input));
        String strLine;

        int i = 0;
        while ((strLine = buf.readLine()) != null) {
            list_.add(strLine);
            i++;
        }

        if (amount > i)
            amount = i;

        for (int j = 0; j < amount; j++)
            out.println("<p><font size=\"" + font_size + "pt\" face=\"Tahoma\">" + list_.get(j) + "</font></p>");

    }

    public void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        doGet(req, resp);
    }
}
